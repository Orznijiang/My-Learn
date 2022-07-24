# Homework 0

作业0的内容主要是进行接下来的作业框架的配置，以及使用配置好的作业框架简单地实现一遍Phong Shading。具体的实现代码在作业文档中已经给出，因此本次作业算是一个对课程作业框架的熟悉。

这里按照作业文档中Visual Studio Code的方法进行配置。

## 环境配置

### 1.下载安装Visual Studio Code

没有安装VS Code的，第一步当然是下载安装Visual Studio Code。这里给出官方链接：

> https://code.visualstudio.com/

Visual Studio Code（简称“VS Code” ）是Microsoft在2015年4月30日Build开发者大会上正式宣布一个运行于 Mac OS X、Windows和 Linux 之上的，针对于编写现代Web和云应用的跨平台源代码编辑器，可在桌面上运行，并且可用于Windows，macOS和Linux。它具有对JavaScript，TypeScript和Node.js的内置支持，并具有丰富的其他语言（例如C++，C＃，Java，Python，PHP，Go）和运行时（例如.NET和Unity）扩展的生态系统。



### 2.安装扩展

打开VS Code后，点击左侧边栏的最后一个图标或快捷键`Ctrl+Shift+X`即可调出扩展界面，可搜索需要的扩展进行安装，如：

* Chinese (Simplified)：将VS Code的界面语言变成简体中文
* Shader languages support for VS Code：识别shader的语言格式并进行修饰
* ……

我们的作业框架要求必需安装插件Live Server，用于本地服务器的搭建（因为作业框架基于WebGL）



### 3.启动服务器

输入快捷键`Ctrl+Shift+P`调出命令行窗口，再输入 `Live Server: Open with Live Server`，或者在VS Code的资源管理器中右键点击html文件，选择`Open with Live Server`，即可使浏览器自动打开指定地址的本地服务器。这时，可以看到类似下面的结果：

![preview](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw0_preview.png?raw=true)

#### 注意

* 不要在未启动本地服务器的情况下直接在外部打开网页文件，会因为模型文件没有加载进来而导致场景是黑的
* 首次启动本地服务器打开网页时，可能（大概率）产生场景中只有“202”图标和一个不断旋转的光源的现象，这时仅需要刷新网页即可



## Phong Shading实现

按照作业文档一步步地进行实现即可。

### 使用 GLSL 语言实现 Phong 模型的 vertexShader 和 fragmentShader

打开 shaders 文件夹中的 InternalShader.js 文件，添加下列两个字符串作为Phong 模型使用到的shader：

```javascript
const PhongVertexShader = `
attribute vec3 aVertexPosition;
attribute vec3 aNormalPosition;
attribute vec2 aTextureCoord;

uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;

varying highp vec2 vTextureCoord;
varying highp vec3 vFragPos;
varying highp vec3 vNormal;

void main(void) {

  vFragPos = aVertexPosition;
  vNormal = aNormalPosition;

  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition , 1.0);

  vTextureCoord = aTextureCoord;
}
`;

const PhongFragmentShader = `
#ifdef GL_ES
precision mediump float;
#endif
uniform sampler2D uSampler;
//binn
uniform vec3 uKd;
uniform vec3 uKs;
uniform vec3 uLightPos;
uniform vec3 uCameraPos;
uniform float uLightIntensity;
uniform int uTextureSample;

varying highp vec2 vTextureCoord;
varying highp vec3 vFragPos;
varying highp vec3 vNormal;

void main(void) {
  vec3 color;
  if (uTextureSample == 1) {
    color = pow(texture2D(uSampler , vTextureCoord).rgb, vec3(2.2));
  } else {
    color = uKd;
  }

  vec3 ambient = 0.05 * color;

  vec3 lightDir = normalize(uLightPos - vFragPos);
  vec3 normal = normalize(vNormal);
  float diff = max(dot(lightDir , normal), 0.0);
  float light_atten_coff = uLightIntensity / length(uLightPos - vFragPos);
  vec3 diffuse = diff * light_atten_coff * color;

  vec3 viewDir = normalize(uCameraPos - vFragPos);
  float spec = 0.0;
  vec3 reflectDir = reflect(-lightDir , normal);
  spec = pow (max(dot(viewDir , reflectDir), 0.0), 35.0);
  vec3 specular = uKs * light_atten_coff * spec;

  gl_FragColor = vec4(pow((ambient + diffuse + specular), vec3(1.0/2.2)), 1.0);
}
`;
```



### 使用 Javascript 语言实现 PhongMaterial 类

该类继承于 Material 类，我们需要在其构造函数中传递对应字符串形式的 vertexShader 和 fragmentShader， 以及 Shader 所需要的变量。在 PhongMaterial 的构造函数 中，会为 PhongShader 所需要的 uniform 和 attribute 变量传递相应的 map 和 array，以及指定要用到的 vertexShader 和 fragmentShader，上述会一起到基类 (Material) 的构造函数中。（需要注意，Material 基类中的 uniforms 默认包含 uModelViewMatrix，uProjectionMatrix，uCameraPos，uLightPos 四个 Shader 常 用的 uniform 变量，这可以简化继承类材质的构造过程）。

```javascript
class PhongMaterial extends Material {

    /**
    * Creates an instance of PhongMaterial.
    * @param {vec3f} color The material color
    * @param {Texture} colorMap The texture object of the material
    * @param {vec3f} specular The material specular coefficient
    * @param {float} intensity The light intensity
    * @memberof PhongMaterial
     */
    constructor(color, colorMap, specular, intensity) {
        let textureSample = 0;

        if (colorMap != null) {
            textureSample = 1;
            super({
                'uTextureSample': { type: '1i', value: textureSample },
                'uSampler': { type: 'texture', value: colorMap },
                'uKd': { type: '3fv', value: color },
                'uKs': { type: '3fv', value: specular },
                'uLightIntensity': { type: '1f', value: intensity }
            }, [], PhongVertexShader, PhongFragmentShader);
        } else {
            //console.log(color);
            super({
                'uTextureSample': { type: '1i', value: textureSample },
                'uKd': { type: '3fv', value: color },
                'uKs': { type: '3fv', value: specular },
                'uLightIntensity': { type: '1f', value: intensity }
            }, [], PhongVertexShader, PhongFragmentShader);
        }

    }
}
```

在实例化 PhongMaterial 并以此进一步构造 MeshRender 类时，MeshRender 的构造函数会调用 material.compile(gl)，该方法自动完成材质用到的 Shader 编 译，以及参数和 Shader 的绑定。由此用户在向材质构造函数中传递完 Shader 用 到的 uniform、attribute 变量后，在 Shader 中就可以认为这些对应的变量可用了。



### 导入PhongMaterial

为了使用编写好的 PhongMaterial 类，在 index.html 中将其导入：

```html
<script src="src/materials/PhongMaterial.js" defer></script>
```

这里需要注意导入文件的顺序，因为 PhongMaterial 继承自 Material 类，所以要 在导入 Material.js 之后导入 PhongMaterial.js。



### 替换原框架中的默认材质

将框架中原来使用的 Material 替换为我们编写好的 PhongMaterial 类。将 load 文件夹中 loadOBJ.js 的下列代码删除（第 40-56 行，该部分 代码只负责创建物体默认基础材质，即表面基础颜色属性，其使用的默认 Shader 不负责高光和环境光着色。除此之外，为了支持无纹理贴图的材质，我们加上了 一点逻辑判断以特殊处理）。

将删除的代码替换成下列代码，这会创建并使用之前新建的 PhongMaterial 实例：

```javascript
let myMaterial = new PhongMaterial(mat.color.toArray(), colorMap, mat.specular.toArray(), renderer.lights[0].entity.mat.intensity);
```



### 参考运行结果

至此，Phong 着色模型的应用就算完成了。如果严格按照上述步骤，此时刷新网页你应该可以看到我们的模型能够与光源进行有趣的交互，并有着不错的光影效果。

![result](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20202/homework_notes/hw0_result.png?raw=true)



## 参考链接

* https://blog.csdn.net/qq_41835314/article/details/125523237
* https://baike.baidu.com/item/Visual%20Studio%20Code/17514281?fromtitle=VS%20Code&fromid=60534513&fr=aladdin