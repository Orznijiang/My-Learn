# Homework 3

作业3的主要内容是将一个可爱的牛牛模型渲染到屏幕上，并添加各种渲染效果。本次作业的坑比较多，文档表述也不太清楚，建议不要一个人硬写，本文将适当给出实现代码。

## 前期准备

* 首先，将之前作业中的观察矩阵和投影矩阵的实现复制到`main.cpp`对应的函数中
* 根据`models`文件夹放置的具体位置，修改`main`函数中的`obj_path`路径
* 同样，根据实际情况修改`LoadFile()`函数中的路径，读取模型文件错误时会在窗口输出错误信息

本人之前作业中的变换矩阵在这次作业中不再完全适用。这是因为，作业中只对模型顶点进行MVP矩阵的变换，并且将normal信息变换到了观察空间中，我这里假定观察空间正向是正Z轴，而作业框架中假定看向-Z轴，这会导致法线在观察空间下的z值不一致。同时，作业框架中直接给出假定摄像机在观察空间中看向Z轴的情况下的光源坐标位置，与我的假定情况不一致，这也会导致光源方向的不一致。要得到与作业结果一致的渲染图，需要在我之前作业的矩阵的基础上做出下述修改：

* 在观察矩阵中，不再反转Z轴

* 在$M_{persp \rightarrow ortho}$矩阵中，使投影后的w值为-z（因为PPT中zNear和zFar的值都小于0，而实际上作业框架中的zNear和zFar都大于0），即修改最后一排为-1：
  $$
  \begin{bmatrix}
  	zNear&0.0&0.0&0.0\\
  	0.0&zNear&0.0&0.0\\
  	0.0&0.0&zNear+zFar&-zNear*zFar\\
  	0.0&0.0&-1.0&0.0
  \end{bmatrix}
  $$

这样，就能使最终结果与文档给出的结果一致。不同的矩阵变换并不意味着孰对孰错，只是定义的方式不一致罢了，重要的是要知道这么写的意义。

## 光栅化及属性插值

光栅化的代码可以参考作业2的实现。不过，相对于作业2，作业3修复了在`draw()`函数中对`w`分量进行其次除法，导致后面得到的`w`分量的值恒为1的问题。这样，我们就可以正确地进行上次作业提到的透视插值校正的操作。

此外，`rasterize_triangle()`函数的参数列表也进行了更新，`t.v`成员修改为`Eigen::Vector4f`以传入`v`值，同时`Triangle`也传入了除顶点信息以外的其他信息（法线信息、uv信息等）；`view_pos`成员主要给出观察空间下的顶点位置，因为作业框架中后面的光照计算全是在观察空间下进行的（这也是为什么之前的矩阵需要修改，若在世界空间下进行就不需要修改）。

在`rasterize_triangle()`函数中，对三角形进行光栅化以及深度测试（参考之前的作业），即遍历包围盒中的像素，当当前像素处于三角形中，且深度小于深度缓冲中的深度时，就可以根据三角形的属性绘制该像素，并更新深度缓存。

### 深度透视插值校正

由于`w`分量保留了观察空间的z分量信息（实际上是-z，因为我们将投影矩阵最后一排修改为了-1，这样，z值越大表示深度越深，距离摄像机越远，符合直觉），根据作业框架的注释以及作业2的参考链接，可以对插值的深度信息进行校正，得到正确的该像素在观察空间下的深度信息：

```
float Z = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
```

深度校正公式：
$$
Z_P=\frac{1}{\frac{\alpha^\prime}{Z_A} + \frac{\beta^\prime}{Z_B} + \frac{\gamma^\prime}{Z_C}}
$$

### 其他属性的插值校正

获得该像素在观察空间中的深度后，可以根据这个信息计算其他需要插值的属性在插值校正后的正确结果，公式如下：
$$
I_P = (\frac{\alpha^\prime}{Z_A}I_A + \frac{\beta^\prime}{Z_B}I_B + \frac{\gamma^\prime}{Z_C}I_C)Z_P
$$
其中 $I$ 表示要插值的属性。

由于我们要插值的属性，包括`float`、`Vector3f`、`Vector2f`等，可以声明一个`auto`的Lambda表达式来统一调用：

```
auto getInterpolateResult = [&](auto& propA, auto& propB, auto& propC) -> auto {
	return Z * (alpha * propA / v[0].w() + beta * propB / v[1].w() + gamma * propC / v[2].w());
};
```

由于`alpha`、`beta`、`gamma`是结构化绑定的参数，是C++17的特性。但在C++20以前，不可以用Lambda 表达式捕获结构化绑定。因此需要将项目的语言属性修改为C++20或以上才能支持上面的表示。具体可查阅参考链接。

结构化绑定：

```
auto [alpha, beta, gamma] = computeBarycentric2D(i + 0.5, j + 0.5, t.v);
```



调用上面的`getInterpolateResult`进行插值操作，例如：

* 对屏幕空间的z值进行插值，用于比较深度（非必要）

  ```
  float zp = getInterpolateResult(v[0].z(), v[1].z(), v[2].z());

* 对顶点颜色进行插值

  ```
  Eigen::Vector3f interpolated_color = getInterpolateResult(color[0], color[1], color[2]);

* 对法线进行插值

  ```
  Eigen::Vector3f interpolated_normal = getInterpolateResult(normal[0], normal[1], normal[2]);
  ```

* 对纹理坐标进行插值

  ```
  Eigen::Vector2f interpolated_texcoords = getInterpolateResult(texcoord[0], texcoord[1], texcoord[2]);

* 对观察空间的坐标进行插值

  ```
  Eigen::Vector3f interpolated_shadingcoords = getInterpolateResult(view_pos[0], view_pos[1], view_pos[2]);
  ```



## 着色器设置

完成属性的插值后，我们需要将计算结果传给需要的着色器，调用着色器得到最终的计算结果，将其设为当前像素的颜色。

### 代码分析

`Shader.hpp`声明了两个结构体`fragment_shader_payload`和`vertex_shader_payload`，分别用来保存片元着色器和顶点着色器的计算过程中需要用到的数据。我们在完成插值属性的计算后，就需要将这些属性赋给他们。

`rasterizer.hpp`中的`rasterizer`类声明了两个包装器对象成员：

```
std::function<Eigen::Vector3f(fragment_shader_payload)> fragment_shader;
std::function<Eigen::Vector3f(vertex_shader_payload)> vertex_shader;
```

模板`function`是在头文件`functional`中声明的，它从调用特征标的角度声明了一个对象，可用于包装调用特征标相同的函数指针、函数对象或Lambda表达式。例如，上面的`fragment_shader`成员，可以将接受一个`fragment_shader_payload`结构体为参数，并返回一个`Eigen::Vector3f`值的任何函数指针、函数对象或Lambda表达式赋给它。例如，有函数声明：

```
Eigen::Vector3f normal_fragment_shader(const fragment_shader_payload& payload);
```

则可以有下面的赋值语句：

```
std::function<Eigen::Vector3f(fragment_shader_payload)> fragment_shader;
fragment_shader = normal_fragment_shader;
```

注意：引用、`const`限定符等不影响特征标的区别。



此外，`rasterizer`类还声明了一个`texture`对象成员：

```
std::optional<Texture> texture;
```

`std::optional`是C++17的新特性，它是一个和类型。简而言之，其声明的变量可以被赋为`<>`中类型的值，也可以被赋为`std::nullopt`，表示没有值。



### 顶点着色器

在本次作业的框架中，顶点着色器并不重要，因为`vertex_shader_payload`结构体仅声明了保存顶点的位置信息的向量，且唯一的`vertex_shader`函数直接返回这个向量，而没有做任何处理：

```
struct vertex_shader_payload
{
    Eigen::Vector3f position;
};

Eigen::Vector3f vertex_shader(const vertex_shader_payload& payload)
{
    return payload.position;
}
```

事实上，我们之前所做的MVP矩阵变换等操作，就是传统的在GPU中的顶点着色器需要完成的操作，而我们已经提前完成了，所以甚至不需要调用这个所谓的“顶点着色器”。



### 片元着色器

首先，根据`fragment_shader_payload`结构体声明一个变量并进行初始化和赋值操作，也就是把之前的插值结果赋给结构体变量：

```
fragment_shader_payload payload(interpolated_color, interpolated_normal.normalized(), interpolated_texcoords, texture ? &*texture : nullptr);
payload.view_pos = interpolated_shadingcoords;
```

至于包装器成员`fragment_shader`的赋值，不需要我们完成，作业框架会根据命令行中的参数的值，对包装器变量进行赋值。至于这些用于赋值的函数的内部实现，后续还是需要我们完成。

```
else if (argc == 3 && std::string(argv[2]) == "normal")
{
	std::cout << "Rasterizing using the normal shader\n";
	active_shader = normal_fragment_shader;
}
```

不过，我们需要以传入插值结果的`fragment_shader_payload`结构体变量为参数，调用当前的`fragment_shader`，获取返回值，并将返回值设置为当前像素的颜色：

```
auto pixel_color = fragment_shader(payload);
set_pixel(Eigen::Vector2i(i, j), pixel_color);
```

注意这里的`set_pixel`函数较上个作业，接口的参数的类型发生了改变，需要进行适当修改，否则无法通过编译：

![参数类型错误](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw3_error1.png?raw=true)



## 具体的片元着色器实现

### normal 着色

将经过映射的法线方向作为最终的颜色输出。这部分作业框架已经为我们实现，可以直接调用输出验证结果。

#### 运行结果参考

![output_normal](https://github.com/Orznijiang/My-Learn/blob/main/Games%20101/homework/Games101_Homework/Assignment_3/output_normal.png?raw=true)



### Blinn-Phong 着色

使用lecture07-lecture08介绍的Blinn-Phong反射模型实现牛牛的光照计算。给出PPT上的公式：

![blinn_phong反射模型](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw3_blinn_phong.png?raw=true)

需要注意的是各种方向向量需要归一化，这里主要区别两个接口的使用方法：

```
light_dir.normalize();
Eigen::Vector3f half = (light_dir + view_dir).normalized();
```

* `normalize()`对进行归一化
* `normalized()`不改变调用它的向量，返回归一化的向量

同时，两个向量值直接相乘无法通过编译，需要调用下面的接口：

```
Eigen::Vector3f deot = kd.cwiseProduct(light.intensity);
```

该函数的作用是将向量的每个分量对应相乘，得到一个新的向量。

此外，环境光的计算应该在光源遍历的循环外面进行，因为环境光与具体的光源无关，不应该多次计算。

#### 运行结果参考

![output_blinn_phong](https://github.com/Orznijiang/My-Learn/blob/main/Games%20101/homework/Games101_Homework/Assignment_3/output_blinn_phong.png?raw=true)



### 加入纹理的 Blinn-Phong 着色

这里，不使用固定的颜色作为漫反射颜色，而是根据纹理的采样颜色作为漫反射颜色`kd`的值。

作业框架提供了`getColor()`用于采样纹理上的值，需要注意的是这里的纹理坐标（uv）可能会超出表示范围（即小于0或大于1），而`getColor()`没有提供越界的处理，因此需要我们手动将纹理坐标的范围映射到合理的值：

```
float u = payload.tex_coords.x() - floor(payload.tex_coords.x());
float v = payload.tex_coords.y() - floor(payload.tex_coords.y());
return_color = payload.texture->getColor(u, v);
```

其中`floor()`为向下取整。

#### 运行结果参考

![output_texture_blinn_phong](https://github.com/Orznijiang/My-Learn/blob/main/Games%20101/homework/Games101_Homework/Assignment_3/output_texture_blinn_phong.png?raw=true)



### bump 着色

这里主要是通过bump texture来改变顶点的法线信息，再将法线信息映射到一个合理值直接绘制出来。

基于原顶点的法线方向normal，通过注释的计算方法可以构建一对相互正交的基，将计算出的t和b看作观察空间下的切线方向（tangent）和副切线方向（bitangent）（实际上不是真正的切线和副切线方向，只是强行构建一对正交基用于模拟切线、副切线和法线构成的TBN矩阵）：

```
auto n = normal.normalized();
auto t = Eigen::Vector3f(
    n.x() * n.y() / sqrt(n.x() * n.x() + n.z() * n.z()),
    sqrt(n.x() * n.x() + n.z() * n.z()),
    n.z() * n.y() / sqrt(n.x() * n.x() + n.z() * n.z())
);
auto b = n.cross(t);

auto tbn_mat = Eigen::Matrix3f();
tbn_mat << t.x(), b.x(), n.x(),
    t.y(), b.y(), n.y(),
    t.z(), b.z(), n.z();
```

示意图大致如下：

![tbn](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw3_tbn.png?raw=true)



然后，对bump纹理进行采样，并根据注释使用采样的结果构建出一个向量作为切线空间中的法线向量，然后对该向量应用tbn矩阵变换，使其变换为观察空间中的法线方向，作为最终的输出。

不过，这里的注释可读性极差，通过作业论坛的信息可知，`h(u,v)`的大致意义为`payload.texture->getColor(u, v).norm()`，即为使用纹理坐标对纹理进行采样，同时调用`norm()`函数，`norm()`函数的返回值是调用向量的长度。因此，向量`ln`的构建如下：

```
auto tex_height = payload.texture->height;
auto tex_width = payload.texture->width;
float u = payload.tex_coords.x() - floor(payload.tex_coords.x());
float v = payload.tex_coords.y() - floor(payload.tex_coords.y());

auto dU = kh * kn * (payload.texture->getColor(u + 1.0f / tex_width, v).norm() - payload.texture->getColor(u, v).norm());
auto dV = kh * kn * (payload.texture->getColor(u, v + 1.0f / tex_height).norm() - payload.texture->getColor(u, v).norm());

auto ln = Eigen::Vector3f(-dU, -dV, 1);
```

这里需要注意的是，纹理坐标的偏移量必须在计算前将其中一个分量转换为浮点数，否则整数除法将使得变异量永远为0。



实际上这里对bump texture的处理并不规范，为了得到与文档中相同的结果，我们严格按照注释中的方法进行处理，但是对于为何这样处理的原因，不必考虑。

#### 运行结果参考

![output_bump](https://github.com/Orznijiang/My-Learn/blob/main/Games%20101/homework/Games101_Homework/Assignment_3/output_bump.png?raw=true)



### displacement 着色

这里的处理和上面的处理大同小异，在得到偏移后的normal向量后，按照注释的方法对顶点进行偏移。同样，这里不需纠结其原因，按照注释进行操作即可。

得到经过处理的顶点位置和法线方向后，我们正常应用之前的Blinn-Phong着色方法对其进行光照计算，得到顶点和法线偏移之后的光照计算结果。

#### 运行结果参考

![output_bump](https://github.com/Orznijiang/My-Learn/blob/main/Games%20101/homework/Games101_Homework/Assignment_3/output_displacement.png?raw=true)



## 提高项

双线性插值写起来不太麻烦，所以就顺便实现了。

根据PPT内容进行纹理的双线性插值采样：

![双线性插值过程](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw3_bilinear.png?raw=true)

主要是根据纹理的坐标得到要采样的4个点的纹理坐标，由于相邻纹素中心点的距离是1，因此计算插值十分便利，直接计算坐标的差即可。之后，调用`std::lerp`进行插值计算，得到最终的输出颜色。

### 运行结果参考

![output_Bilinear_texture_blinn_phong](https://github.com/Orznijiang/My-Learn/blob/main/Games%20101/homework/Games101_Homework/Assignment_3/output_Bilinear_texture_blinn_phong.png?raw=true)

可以看到，提升还是非常明显的。



## 参考链接

* 结构化绑定：https://blog.csdn.net/fpcc/article/details/121992645
* https://blog.csdn.net/qq_45065475/article/details/105906539
* 作业2：https://zhuanlan.zhihu.com/p/535088979
* https://blog.csdn.net/TA_tan/article/details/124861929
* https://blog.csdn.net/u012294613/article/details/124889172
* https://blog.csdn.net/qq_45065475/article/details/105906539
* https://zhuanlan.zhihu.com/p/509902950
* https://games-cn.org/forums/topic/%e4%bd%9c%e4%b8%9a3%e6%9b%b4%e6%ad%a3%e5%85%ac%e5%91%8a/
* https://games-cn.org/forums/topic/displacement-shader%e9%ab%98%e5%85%89%e8%ae%a1%e7%ae%97%e7%bb%93%e6%9e%9c%e5%81%8f%e5%b7%ae%e5%a4%a7%e5%8a%a9%e6%95%99%e5%b8%ae%e7%9c%8b%e7%9c%8b/
* https://games-cn.org/forums/topic/%e5%85%b3%e4%ba%8ebump%e5%92%8cdisplacement-shader%e9%87%8chuv%e5%92%8cposition-p%e7%9a%84%e7%90%86%e8%a7%a3/
* https://blog.csdn.net/m0_56348460/article/details/117386857