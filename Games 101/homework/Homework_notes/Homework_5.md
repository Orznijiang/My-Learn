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

* 一个结构体，定义了 Ray 与 物体 的交点应保存的信息
* Renderer类，其中的`Render()`函数实现了对参数`scene`的光线追踪渲染，并将结果保存到图片中

