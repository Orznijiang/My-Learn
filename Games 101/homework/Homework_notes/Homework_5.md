# Homework 5

作业5的主要内容是实现基本的经典Whitted-Style Ray Tracing算法。

作业框架已经为我们提供了大部分的实现，需要补充的代码非常少，主要是初始的Primary Ray的生成部分以及Ray与三角形的求交判断部分。该部分的知识集中在Lecture 13中。

## 代码分析

### Vector

由于本次作业框架不再使用Eigen库，因此提供了向量类的实现，并提供了完成作业所需要的向量操作，如点积（`dotProduct()`）、叉积（`crossProduct()`）、归一化（`normalize()`）等。

### Object

场景中所有渲染物体的基类，定义了物体的材质信息，以及纯虚函数`intersect()`和`getSurfaceProperties()`。前者用于判断物体与传入的Ray是否相交，并在相交时返回一定的信息。后者用于计算返回与相交点相关的属性信息（与相交点无关的属性信息可以直接取到）。该基类的派生类必须实现这两个纯虚函数才能够进行实例化。

#### Sphere

用于在场景中模拟球，继承自Object类。

* `intersect()`使用Lecture 13中介绍的代数方法计算交点
* `getSurfaceProperties()`根据交点位置返回交点的法线方向

#### Triangle

用于在场景中模拟三角形Mesh集合，继承自Object类。

* `intersect()`遍历Mesh中的每个三角形并计算交点。其在循环中调用`rayTriangleIntersect()`函数，使用Lecture 13中介绍的`Moller-Trumbore`方法计算Ray与该三角形面片的交点。这部分的代码需要我们完成
* `getSurfaceProperties()`根据索引`index`，计算该索引的三角形的法线信息，并通过交点的重心坐标插值出纹理坐标信息

### global

定义了整个框架会用到的一些基本函数和变量。

### Light

定义了一个基础的光源类。

### Scene

定义了要渲染的场景。

包含了一些必要的参数，如：

* 相机渲染相关的`width`、`height`、`fov`等
* 两个容器，用于保存场景中的物体和灯光信息
* Ray Tracing 递归的最大深度
* ……


### Renderer

* 一个结构体`hit_payload`，定义了 Ray 与 物体 的交点应保存的信息
* Renderer类，其中的`Render()`函数实现了对参数`scene`的光线追踪渲染，并将结果保存到图片中

#### Render()

* 根据`width`和`height`声明一个名为`framebuffer`的向量数组，用于保存计算结果。`width`和`height`可视为要生成图片的水平方向的像素数量和竖直方向的像素数量
* 遍历每个像素，生成一条射线，调用`castRay()`方法，使其开始在场景里进行tracing，存储返回的颜色。生成Primary Ray的过程需要我们完成
* 将`framebuffer`的内容保存到图片中

#### trace()

测试当前Ray是否与场景中的物体存在交点。若存在，返回由最近的交点构建的`hit_payload`信息。

#### castRay()

一个递归调用的方法，每次调用，都将函数参数内的深度值递增。

* 若当前递归深度达到最大深度（scene 定义），返回（0,0,0）
* 若当前递归深度未达到最大深度，对当前Ray调用`trace()`方法，若存在交点：
  * 调用`getSurfaceProperties()`方法获取顶点相关的属性信息
  * 根据相交的物体的类型分别进行处理
    * 反射和折射（REFLECTION_AND_REFRACTION）
      * 计算出反射方向，调用`castRay()`方法进行tracing，得到返回颜色
      * 计算出折射方向，调用`castRay()`方法进行tracing，得到返回颜色
      * 计算菲涅尔项，即反射和折射的比值，获得混合颜色
    * 反射（REFLECTION）
      * 计算出反射方向，调用`castRay()`方法进行tracing，得到返回颜色
      * 计算菲涅尔项，将返回颜色乘上反射项的系数，得到混合颜色
    * 默认
      * 使用Phong模型进行着色（没有diffuse项，默认为完美反射）
        * 对于每一个光源，创建一个Shadow Ray，调用`trace()`方法。若存在交点且距离小于到光源的距离，则在阴影中
        * 计算漫反射项
        * 计算高光项（这里高光项没有考虑阴影，不知道为什么）
      * 返回颜色
* 返回颜色



## Primary Ray的生成

首先，注意到框架中给出的Primary Ray的初始化坐标：

```c++
Vector3f dir = Vector3f(x, y, -1);
```

相机的初始坐标在原点：

```
Vector3f eye_pos(0);
```

因此，初始化的Primary Ray的终点永远在`Z = -1`的平面上。据此，对于每一条指向某一个像素中心的Primary Ray，我们需要计算出其在终点的z值为-1时的坐标，再将其归一化。

由相机的fov值，可以很快计算出相机的视锥体投影到`Z = -1`的平面上的竖直距离，这也应该是所有像素投影到这个平面上的范围。因此，将这个范围除以竖直方向的像素数（Height），即可得到每一个像素在该平面上的竖直跨度距离。又由于像素是正方形，竖直跨度距离与水平跨度距离相等。

然后，我们需要计算遍历开始前的初始位置。经测试，这里图像的像素索引从左上角开始，即，初始的像素坐标为`（-width/2， height/2）`，可据此计算出`Z = -1`平面上的初始位置。

对于每一对像素索引，我们在初始位置的基础上进行偏移，计算出分别在水平方向和竖直方向偏移相应个像素长度后的位置。注意，要在两个方向上额外平移0.5个像素长度，以指向像素的中心位置。这样，就可以得到Primary Ray的方向。



## Ray与三角形的求交判断

使用Lecture 13中介绍的`Moller-Trumbore`方法，可以很快计算出Ray与三角形是否有交点，以及交点相对于三角形三个顶点的重心坐标。实际上，该方法就是将射线的表示方程与重心坐标的表示方程联立起来，再应用克莱姆法则求解的过程（三个等式（x、y、z）三个未知数：t、b~1~、b~2~）。克莱姆法则是线性代数的内容，不了解的同学可以查询相关资料。

![Möller_Trumbore](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw5_M%C3%B6ller_Trumbore.png?raw=true)

计算出，t、b~1~、b~2~后，我们判断是否真实存在交点：

* t > 0
* b~1~ > 0
* b~2~ > 0
* b~1~ + b~2~ < 1

满足上面的条件，则是真实存在射线与三角形内部的交点。除了返回t值，还需要返回重心坐标：

```
u = b1;
v = b2;
```

重心坐标在后面插值计算纹理坐标的时候会使用到。这里u、v两个形参的名字非常具有迷惑性。



## 参考运行结果

![result](https://github.com/Orznijiang/My-Learn/blob/main/Games%20101/homework/Games101_Homework/Assignment_5/binary.png?raw=true)
