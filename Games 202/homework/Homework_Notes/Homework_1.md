# Homework 1

作业1的内容主要是实现实时渲染管线中的阴影计算，包括经典的Two Pass Shadow Map 方法产生的硬阴影，以及PCF(Percentage Closer Filter) 和PCSS(Percentage Closer Soft Shadow)的软阴影实现。该部分的知识集中在Lecture 03和Lecture 04中。

作业框架已经为我们提供了大部分的实现，作业的主要内容将集中在 shader 内函数的完善上：

* 对于场景中的每个物体都会默认附带一个 ShadowMaterial 材质，并会在调用 loadOBJ 时添加到 WebGLRenderer 的 shadowMeshes[] 中。当光源参数hasShadowMap 为 true 时，作业框架将开启 Shadow Map 功能，在正式渲染场景之前会以 ShadowMaterial 材质先渲染一遍 shadowMeshes[] 中的物体，从而生成我们需要的 ShadowMap。在 engine.js 中，可以看到创建了一个开启 ShadowMap 的方向光：

  ![turn on shadowmap](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_shadowmap_on.png?raw=true)

* ShadowMaterial 将使用 Shader/shadowShader 文件夹下的顶点和片元着色器。实现该材质的重点是要向 ShadowVertex.glsl 传递正确的 uLightMVP变量

* 在正确实现 Shadow Map 之后，实现 PCF、PCSS 的主要工作将集中在 glsl的编写上

关于作业框架的基本解读，可查阅下方的参考链接。



## 光源的变换矩阵实现

要得到一张 Shadow Map ，我们需要以光源的位置对场景进行渲染，从而得到一张深度图。在 ShadowMaterial.js 中需要向 Shader 传递正确的 uLightMVP 矩阵，其调用了 light 中的 CalcLightMVP 函数。因此，我们首先需要完成 DirectionalLight 中的 CalcLightMVP(translate, scale) 函数，它会在 ShadowMaterial 中被调用，返回光源处的 MVP 矩阵从而完成参数传递过程。

实际上，Shadow Map 的绘制，就相当于将一个摄像机摆在光源的位置，朝向光源的方向，根据需求确定渲染的范围，然后对场景进行渲染，得到在该位置的每个像素上的最近点的深度值。

这里涉及到了矩阵的计算，作业框架中使用了glMatrix库，这是 JavaScript 针对 WebGL 的矩阵向量库，其接口文档可查阅下方参考链接。



### 模型矩阵

一般的模型矩阵由缩放矩阵、旋转矩阵、位移矩阵依次构成。这里我们注意到 MeshRender.js 中的 bindCameraParameters 函数，其模型矩阵的构建先调用位移方法，再调用缩放方法，没有调用旋转方法：

```javascript
// Model transform
mat4.identity(modelMatrix);
mat4.translate(modelMatrix, modelMatrix, this.mesh.transform.translate);
mat4.scale(modelMatrix, modelMatrix, this.mesh.transform.scale);
```

实际上，这里的矩阵计算将变换矩阵放在右边，相当于每次调用都在右边添加一个变换，最终对向量进行变换时，越右边的矩阵越早进行计算，因此，这里实际上的顺序还是先缩放，再位移。

根据上面的写法，我们使用传入的 translate 和 scale 参数构建 light 的模型矩阵：

```javascript
// Model transform
mat4.identity(modelMatrix);
mat4.translate(modelMatrix, modelMatrix, translate);
mat4.scale(modelMatrix, modelMatrix, scale);
```



### 观察矩阵

光源包含 lightPos、focalPoint、lightUp 3个成员变量，我们可以使用这3个变量构建出观察矩阵，即将光源视为一个摄像机进行处理。这里，我们可以直接调用glMatrix库提供的接口：

```javascript
// View transform
mat4.identity(viewMatrix);
mat4.lookAt(viewMatrix, this.lightPos, this.focalPoint, this.lightUp);
```

lookAt 方法根据这3个信息构建出从当前坐标系转换到观察坐标系的矩阵，其构建过程在下方参考链接给出。



### 投影矩阵

投影包括正交投影和透视投影，这里推荐使用正交投影，因为这样可以保证场景深度信息在坐标系转换中保持线性关系从而便于之后的使用。正交投影的参数（width、height、near、far等）决定了 Shadow Map 所覆盖的范围，这个范围是由我们自己决定的，过小的范围会导致阴影被截断，过大的范围会导致精度的降低，因此需要合理选择。

这里，我们依旧调用glMatrix库提供的接口：

```javascript
// Projection transform
mat4.identity(projectionMatrix);
mat4.ortho(projectionMatrix, -120, 120, -120, 120, 0.1, 500);
```

接口参数解析：

```
// Generates a orthogonal projection matrix with the given bounds
(static) ortho(out, left, right, bottom, top, near, far) → {mat4}
```

| Name     | Type   | Description                              |
| :------- | :----- | :--------------------------------------- |
| `out`    | mat4   | mat4 frustum matrix will be written into |
| `left`   | number | Left bound of the frustum                |
| `right`  | number | Right bound of the frustum               |
| `bottom` | number | Bottom bound of the frustum              |
| `top`    | number | Top bound of the frustum                 |
| `near`   | number | Near bound of the frustum                |
| `far`    | number | Far bound of the frustum                 |



这样，我们就完成了 lightMVP 矩阵的构建。



## Shadowmap 绘制

在绘制 Shadow Map 以及正常的渲染中，我们都会使用到上面的 lightMVP 矩阵。其中，shadow pass 的实现已经在作业框架中提供。

### vert

直接使用 lightMVP 矩阵对顶点进行变换：

```glsl
gl_Position = uLightMVP * vec4(aVertexPosition, 1.0);
```

### frag

这里使用到了 gl_FragCoord.z，你可以理解为当前片元的深度值，且范围在 0 ~ 1 之间，值越大表示深度越深，同时由于我们的投影矩阵是正交矩阵，这个深度值是线性的。具体关于这个值的含义可以查阅下方的参考链接。

这里，我们调用 pack 函数将深度的 float 值包装入输出的4个通道中：

```glsl
vec4 pack (float depth) {
    // 使用rgba 4字节共32位来存储z值,1个字节精度为1/256
    const vec4 bitShift = vec4(1.0, 256.0, 256.0 * 256.0, 256.0 * 256.0 * 256.0);
    const vec4 bitMask = vec4(1.0/256.0, 1.0/256.0, 1.0/256.0, 0.0);
    // gl_FragCoord:片元的坐标,fract():返回数值的小数部分
    vec4 rgbaDepth = fract(depth * bitShift); //计算每个点的z值
    rgbaDepth -= rgbaDepth.gbaa * bitMask; // Cut off the value which do not fit in 8 bits
    return rgbaDepth;
}

void main(){
  gl_FragColor = pack(gl_FragCoord.z);
}
```

这样，光源的深度信息就被输出到了一张纹理中。



## 利用 Shadowmap 绘制阴影

在正常的渲染 pass 中，我们对 Shadow Map 采样，将采样的结果与当前片元的深度进行比较，从而判断当前的片元是否处于阴影中。

### vert

对顶点进行常规的 MVP 矩阵变换，同时还需要使用 lightMVP 矩阵进行变换，计算以光源为视点的坐标，并传递到片元着色器中，使得其能在片元着色器中与 Shadow Map 的采样值进行比较：

```
gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aVertexPosition, 1.0);
vPositionFromLight = uLightMVP * vec4(aVertexPosition, 1.0);
```



### frag

main() 中已经为我们定义好了一些接口：

```glsl
float visibility;
//visibility = useShadowMap(uShadowMap, vec4(shadowCoord, 1.0));
//visibility = PCF(uShadowMap, vec4(shadowCoord, 1.0), 5.0);
visibility = PCSS(uShadowMap, vec4(shadowCoord, 1.0));
vec3 phongColor = blinnPhong();
gl_FragColor = vec4(phongColor * visibility, 1.0);
//gl_FragColor = vec4(phongColor, 1.0);
```

通过调用计算阴影的函数，我们得到一个表示可见性的 float 值，使用这个值对 Blinn-Phong 的光照结果进行影响，得到包含阴影的光照结果。其中 uShadowMap 即为我们在 shadow pass 中计算出来的 ShadowMap 纹理，shadowCoord 用于对 ShadowMap 进行采样和比较深度。

首先，需要将 vPositionFromLight 的坐标范围映射到 0 ~ 1 之间，因为纹理采样的坐标范围是 0 ~ 1 ，Shadowmap 中存储的纹理深度范围也是 0 ~ 1 ：

```glsl
vec3 shadowCoord = ((vPositionFromLight.xyz / vPositionFromLight.w) + 1.0) / 2.0;
```

这里的齐次除法可有可无，因为正交投影理论上w值恒为1.0。vPositionFromLight处于正交投影后的裁剪坐标系中，坐标范围为 -1.0 ~ 1.0 ，上面的计算将其范围缩限到 0 ~ 1 。



#### 硬阴影

硬阴影的实现需要我们完善 phongFragment.glsl 中的 useShadowMap 函数。该函数负责查询当前着色点在 ShadowMap 上记录的深度值，并与转换到 light space 的深度值比较后返回 visibility 项。请注意，使用的查询坐标需要先转换到 NDC 标准空间 [0,1]。

作业框架提供了 unpack 接口，用于从纹理信息中还原深度信息：

```glsl
float unpack(vec4 rgbaDepth) {
    const vec4 bitShift = vec4(1.0, 1.0/256.0, 1.0/(256.0*256.0), 1.0/(256.0*256.0*256.0));
    return dot(rgbaDepth, bitShift);
}
```

我们首先使用片元在 light space 中的坐标对 ShadowMap 采样，并调用 unpack  函数得到存储的深度值。然后，通过将该深度值与当前片元在 light space 中的深度值进行比较，来判断可见性（硬阴影的可见性非0即1）：

```glsl
vec4 packedShadowDepth = texture2D(shadowMap, shadowCoord.xy).rgba;
float shadowDepth = unpack(packedShadowDepth);
if(shadowCoord.z > shadowDepth){
  return 0.0;
}
return 1.0;
```

##### 参考运行结果

![2p_result_no_bias](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_2p_result_no_bias.png?raw=true)

可以观察到，在阴影的边界处（特别是光线方向与顶点法线方向夹角较大的情况下）容易出现阴影瑕疵（shadow acne），这是由于 ShadowMap 的精度问题（采样率低）而产生的自遮挡（self occlusion）现象，在Lecture 03中有相关的论述。我们可以引入 bias 来对阴影纹理的采样值进行一定程度的偏移来处理自遮挡问题，但这种处理方式同样会产生新的问题，即漏光现象，一些本应处于阴影中的位置被意外地照亮了。关于 shadow bias 的进一步论述可参考下面的文章。

![2p_result_with_bias](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_2p_result_with_bias.png?raw=true)



#### PCF(Percentage Closer Filtering)

PCF 的实现需要我们完善 phongFragment.glsl 中的 PCF 函数。区别于硬阴影，其总体思路为对采样点周围的一片区域进行采样，计算顶点被这些采样点遮挡的总体数量，再除以采样点的数量，作为该点被遮挡的程度系数。因此，它不是一个非0即1的数，而是一个浮点数。

作业框架推荐在一个圆盘滤波核中进行随机采样，采用这种方案的原因是可以简化后续PCSS Shader 的编写同时可以使软阴影上模糊的部分更显圆润自然，计算出来的半影直径可与单位圆盘上的采样点相乘生成 ShadowMap 上的采样坐标。

值得注意的是随机采样函数的质量将与最终渲染效果的好坏息息相关，作业框架中提供了泊松圆盘采样和均匀圆盘采样两种采样函数，替换使用对比一下两种采样函数的细微区别，参考链接中给出了两种采样方式的可视化展示。在实际的使用中，确实是泊松圆盘采样的效果更好一些。

```glsl
#define NUM_SAMPLES 100
#define BLOCKER_SEARCH_NUM_SAMPLES NUM_SAMPLES
#define PCF_NUM_SAMPLES NUM_SAMPLES

vec2 poissonDisk[NUM_SAMPLES];

void poissonDiskSamples( const in vec2 randomSeed ) {

  float ANGLE_STEP = PI2 * float( NUM_RINGS ) / float( NUM_SAMPLES );
  float INV_NUM_SAMPLES = 1.0 / float( NUM_SAMPLES );

  float angle = rand_2to1( randomSeed ) * PI2;
  float radius = INV_NUM_SAMPLES;
  float radiusStep = radius;

  for( int i = 0; i < NUM_SAMPLES; i ++ ) {
    poissonDisk[i] = vec2( cos( angle ), sin( angle ) ) * pow( radius, 0.75 );
    radius += radiusStep;
    angle += ANGLE_STEP;
  }
}

void uniformDiskSamples( const in vec2 randomSeed ) {

  float randNum = rand_2to1(randomSeed);
  float sampleX = rand_1to1( randNum ) ;
  float sampleY = rand_1to1( sampleX ) ;

  float angle = sampleX * PI2;
  float radius = sqrt(sampleY);

  for( int i = 0; i < NUM_SAMPLES; i ++ ) {
    poissonDisk[i] = vec2( radius * cos(angle) , radius * sin(angle)  );

    sampleX = rand_1to1( sampleY ) ;
    sampleY = rand_1to1( sampleX ) ;

    angle = sampleX * PI2;
    radius = sqrt(sampleY);
  }
}
```

分析代码，可以看到两个采样方法都在一个单位圆内随机地生成二维坐标向量，并根据 NUM_SAMPLES 的值确定采样点的数量，最后将生成的采样坐标存储在 poissonDisk 数组中。

在 PCF() 中，我们首先调用采样函数，生成一系列的采样点。这里的 randomSeed 可以是任意值，如顶点的xy分量，因为这在每个片元中的值一般不同。然后，我们遍历 poissonDisk 数组，根据每一个采样点的坐标，计算其在 Shadowmap 采样时的 uv 偏移值，然后将采样得到的深度值与当前顶点在 light space 的深度值比较，若判断顶点存在于阴影中，则将计数器+1。最后，不存在于阴影中的采样点与采样点总数的比值即为该点的可见程度：

```glsl
poissonDiskSamples(coords.xy);
float blocker = 0.0;
for(int i = 0; i < NUM_SAMPLES; i++){
  vec2 uv_bias = poissonDisk[i] * radius / 2048.0;
  float shadowDepth = unpack(texture2D(shadowMap, coords.xy + uv_bias));
  if(coords.z > shadowDepth + EPS){
    blocker++;
  }
}
return 1.0 - blocker / float(NUM_SAMPLES);
```

关于 uv 的偏移值，由于上面生成的采样点处于单位圆内，因此可以使用一个 radius 来控制整体的采样范围。由于作业框架 Shadowmap 的大小为 2048 x 2048，每个像素的长度可以近似为 1 / 2048。因此，上面的计算可以表示出采样点在 uv 坐标中的偏移。



##### 参考运行结果

![PCF：radius=5.0](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_PCF_5.png?raw=true)

![PCF：radius=25.0](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_PCF_25.png?raw=true)

可以看到，阴影的质量有了比较大的提升，同时采样数量与阴影质量的关系也比较大。



####  PCSS(Percentage Closer Soft Shadow)

PCSS 的实现需要我们完善 phongFragment.glsl 中的 findBlocker 和 PCSS 函数。

作业文档注释：请注意，为了使本轮工作的重心放在算法的核心实现上，诸如光源宽度、采样数之类的参数可以通过 #define 直接定义使用。同时请保证使用的数据具有统一标架，而不是简单的套用公式。



##### avgblocker depth

其中， findBlocker 函数中需要我们完成对遮挡物平均深度的计算。首先，还是调用采样函数，生成一系列的采样点。然后遍历数组，对于每一个偏移的 uv 坐标采样到的深度，若其产生了遮挡，则进行计数。最终计算得到被遮挡的平均深度。

这里需要注意的是要考虑没有遮挡的情况，即计数为0，此时在计算遮挡的平均深度时会发生除数为0的情况。

同时，uv 偏移半径的选择对最终的结果也非常重要。由于远处的物体更容易被遮挡，当选择固定的较小的 radius 值时，其对距离光源较远的顶点进行平均遮挡深度的计算可能无法很好的表现出其被遮挡的程度（因为光源实际上是有一定形状的，而不是理想的无体积点，距离光源越远，光源的不同部分就越有可能被遮挡，从而无法对该点的照明做出贡献）。

![small blocker](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_small_blocker.png?raw=true)

在采样数较多的情况下，这种缺陷会被放大，较小的 radius 会导致距离光源较远处的阴影边缘处的过渡很生硬，这正是因为较小的采样半径使得距离光源较远处的顶点采样时的平均遮挡深度过渡很生硬（可以类比模糊操作，使用较小的卷积核对边缘锐利处的模糊作用并不明显），下面是出现上面这种问题时的平均遮挡深度的可视化：

![blocker_visualization](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_blocker_visualization.png?raw=true)

这种剧烈的平均遮挡深度的变化会导致计算的半影直径的剧烈变化，从而导致最后的 PCF 采样半径在边缘处的突变，从而使边缘处的阴影过渡生硬。

然而，过大的 radius 同样存在问题，即计算出的平均遮挡深度无法准确表示该点的被遮挡情况，顶点周围的平均遮挡深度相似，从而导致计算出的半影直径相似，无法表现出距离越远阴影越模糊的效果。

因此，我们考虑使用自适应的采样半径 radius，将 radius 与光源宽度、视锥体宽度关联起来，这里的光源宽度、视锥体宽度都是自定义的值，其中视锥体的宽度就是我们正交投影所使用的截面体的宽度。顶点距离光源越远，其在 Shadowmap 上的成像范围就越大，应使用更大的采样半径，反之则使用更小的采样半径，如下图所示：

![optimize_avg_depth](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_optimize_avg_depth.png?raw=true)

据此，可以得到采样 uv 的偏移公式：

```glsl
vec2 uv_bias = poissonDisk[i] * zReceiver * LIGHT_WIDTH / CAMERA_WIDTH / 2.0;
```

其中 2.0 是调整最终计算结果的一个 trick。



##### penumbra size

根据前面计算出来的平均遮挡深度，我们可以利用相似三角形的性质计算出半影直径：

![penumbra_size](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_penumbra_size.png?raw=true)

在 Lecture 03 中有比较详细的讲解，这里不再解释。



##### filtering

这里实际上就是做一次 PCF ，只不过 PCF 的偏移 uv 不再固定，而是根据上面计算出来的半影直径动态地调整，距离遮挡点越远的顶点，使用越大的偏移半径。由于这部分的代码与 PCF 的计算完全相同，我们可以对 PCF 函数的接口稍作修改，然后直接进行调用：

```glsl
float PCF(sampler2D shadowMap, vec4 coords, float radius) {
  // ......
}
float PCSS(sampler2D shadowMap, vec4 coords){

  // STEP 1: avgblocker depth
  // ......

  // STEP 2: penumbra size
  // ......

  // STEP 3: filtering 
  return PCF(shadowMap, coords, penumbra + 2.0);
}
```

这里我将计算出的 penumbra 加上一个常数半径，避免在较近处出现硬阴影的自遮挡瑕疵。



##### 参考运行结果

![result_PCSS](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_result_PCSS.png?raw=true)

可以看到，在遮挡点距离顶点较近时阴影较锐利，反之则较模糊。



![add_ambient](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw1_add_ambient.png?raw=true)

在最终结果下加入环境光照明，避免阴影处全黑。



很多情况下最终渲染出现条状瑕疵，排除自遮挡问题后依旧存在，可能是浮点计算的精度问题。



## 参考链接

* [1] 代码框架分析：https://blog.csdn.net/qq_41835314/article/details/125619239
* [2] glMatrix：[JSDoc: Module: mat4 (glmatrix.net)](https://glmatrix.net/docs/module-mat4.html)
* [3] LookAt：https://learnopengl-cn.github.io/01%20Getting%20started/09%20Camera/
* [4] gl_FragCoord：https://zhuanlan.zhihu.com/p/102068376
* [5] shadow bias：https://zhuanlan.zhihu.com/p/370951892
* [6] [Sampling function (codepen.io)](https://codepen.io/arkhamwjz/pen/MWbqJNG?editors=1010)
* [7] https://games-cn.org/forums/topic/yigeguanyuzuoyeyiwenti/
* [8] https://games-cn.org/forums/topic/zuoye1dezhengjiaojuzhencanshudeyihuo/
* [9] https://blog.csdn.net/qq_41835314/article/details/125726339?spm=1001.2014.3001.5502