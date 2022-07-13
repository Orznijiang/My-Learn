# Homework 7

作业6的主要内容是在作业5实现的经典Whitted-Style Ray Tracing算法的基础上加入物体划分算法 Bounding Volume Hierarchy (BVH) ，使得求交的过程得到加速。该部分的知识集中在Lecture 13和Lecture 14中。

作业框架已经为我们提供了大部分的实现，包括BVH结构的递归构建。在理解框架的大部分实现后，我们所需要补充的代码为 Ray-Bounding Volume 求交过程与 BVH 的查找过程。同时需要迁移上个作业中自己实现的代码。

首先，或许需要修改模型文件的读取路径，取决于你的放置位置：

```c++
MeshTriangle floor("models/cornellbox/floor.obj", white);
MeshTriangle shortbox("models/cornellbox/shortbox.obj", white);
MeshTriangle tallbox("models/cornellbox/tallbox.obj", white);
MeshTriangle left("models/cornellbox/left.obj", red);
MeshTriangle right("models/cornellbox/right.obj", green);
MeshTriangle light_("models/cornellbox/light.obj", light);
```



## 代码分析

### global

定义了整个框架会用到的一些基本函数和变量。

### Vector

由于本次作业框架不再使用Eigen库，因此提供了向量类的实现，并提供了完成作业所需要的向量操作，如点积（`dotProduct()`）、叉积（`crossProduct()`）、归一化（`normalize()`）等。

### Object

场景中所有渲染物体的基类，与作业5的框架不同，这里不再包含物体的材质信息。同时纯虚函数的数量也增加了：

* `virtual bool intersect(const Ray& ray) = 0`
  * 判断是否相交
* `virtual bool intersect(const Ray& ray, float &, uint32_t &) const = 0`
  * 判断是否相交，并将一些值传入引用参数
* `virtual Intersection getIntersection(Ray _ray) = 0`
  * 判断是否相交，并将返回一个`Intersection `对象（保存了交点信息）
* `virtual void getSurfaceProperties(const Vector3f &, const Vector3f &, const uint32_t &, const Vector2f &, Vector3f &, Vector2f &) const = 0`
  * 根据重心坐标等信息，计算出交点处的表面材质信息，传入引用参数
* `virtual Vector3f evalDiffuseColor(const Vector2f &) const = 0`
  * 返回漫反射颜色
* `virtual Bounds3 getBounds() = 0`
  * 返回物体的包围盒

#### Sphere

用于在场景中模拟球，继承自Object类。

* 包含圆心、半径、半径平方和指向材质对象的指针
* 实现所有纯虚函数



与作业5的框架不同，这里声明了一个三角形类用于保存单个的三角形信息

#### Triangle

用于在场景中模拟三角形，继承自Object类。

* 包含顶点坐标、边向量、纹理坐标、法线方向和指向材质对象的指针
* 实现所有纯虚函数

#### MeshTriangle

用于在场景中模拟多个三角形组成的Mesh，继承自Object类（不是Triangle）。

* 成员属性：
  * `bounding_box`：该Mesh的包围盒
  * `vertices`：顶点集合
  * `numTriangles`：三角形数量
  * `vertexIndex`：顶点索引
  * `stCoordinates`：纹理坐标
  * `triangles`：Triangle对象的容器
  * `bvh`：指向该Mesh重建的BVH结构的root的指针
  * `m`：指向材质对象的指针
* 实现所有纯虚函数



### Bounds3

包围盒类，每个包围盒可由 pMin 和 pMax 两点描述。

* `Bounds3::Union` 函数的作用是将两个包围盒并成更大的包围盒
* 与材质一样，场景中的每个物体实例都有自己的包围盒

### BVH

 BVH 加速类，本次作业的重点。

* 场景 scene 拥有一个 BVHAccel 实例
* 从根节点开始，我们可以递归地从物体列表构造场景的 BVH

#### BVHBuildNode

BVH结构的节点对象，包含

* `bounds`：该节点的包围盒
* `left`：该节点的左子节点指针，叶子结点为空
* `right`：该节点的右子节点指针，叶子结点为空
* `object`：该节点下的Object指针，非叶子结点为空

在该是线下，每个叶子节点只指向一个模型。

#### BVHAccel

管理一个完整的BVH结构，保存一个根节点的指针以及指向所有Object物体的指针容器。下面介绍其中比较重要的函数实现。

##### recursiveBuild()

递归函数，对于一个保存Object物体的指针的容器：

* 创建一个新的`BVHBuildNode`对象

* 若容器内只剩下一个Object对象

  * 该节点为叶子节点
  * 左右子节点设为空指针
  * object成员变量指针指向该对象
  * 计算该对象的包围盒，赋给bounds成员变量

* 若容器内有两个Object对象

  * 该节点非叶子结点
  * object指针为空指针
  * 左右子节点分别为对两个Object对象指针递归调用recursiveBuild()的返回指针
  * 包围盒为左右子节点的和

* 若容器内有两个以上的Object对象

  * 则需要使用算法将它们分成两部分

  * 对于每一个Object对象的包围盒，计算出其包围盒的中心，以这些包围盒的中心坐标建立一个新的包围盒

    ```c++
    for (int i = 0; i < objects.size(); ++i)
    	centroidBounds = Union(centroidBounds, objects[i]->getBounds().Centroid());
    ```

  * 确认上面生成的包围盒在XYZ哪个维度上的跨度最大，然后在该维度上，以每个Object对象的包围盒的中心为比较对象，对Object对象进行排序

    ```c++
    int dim = centroidBounds.maxExtent();
    switch (dim) {
    case 0:
        std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
            return f1->getBounds().Centroid().x <
                   f2->getBounds().Centroid().x;
        });
        break;
    case 1:
        std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
            return f1->getBounds().Centroid().y <
                   f2->getBounds().Centroid().y;
        });
        break;
    case 2:
        std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
            return f1->getBounds().Centroid().z <
                   f2->getBounds().Centroid().z;
        });
        break;
    }
    ```

  * 将排序后的Object对象平分到两个容器中，分别作为递归调用recursiveBuild()的参数，将返回值分别赋给左右子节点

    ```c++
    auto beginning = objects.begin();
    auto middling = objects.begin() + (objects.size() / 2);
    auto ending = objects.end();
    
    auto leftshapes = std::vector<Object*>(beginning, middling);
    auto rightshapes = std::vector<Object*>(middling, ending);
    
    node->left = recursiveBuild(leftshapes);
    node->right = recursiveBuild(rightshapes);
    ```

  * 包围盒为左右子节点的和



##### Intersect()

从根节点开始调用getIntersection()函数，getIntersection()是一个递归函数，最终返回交点信息。

##### getIntersection()

对于每个node，递归调用其左子节点和右子节点，得到最终的交点并返回。该部分需要我们自己实现。



### Light

定义了一个基础的光源类。

#### AreaLight

定义了一个面光源，继承自Light类。



### Renderer

* 一个结构体`hit_payload`，定义了 Ray 与 物体 的交点应保存的信息
* Renderer类，其中的`Render()`函数实现了对参数`scene`的光线追踪渲染，并将结果保存到图片中

#### Render()

* 根据`width`和`height`声明一个名为`framebuffer`的向量数组，用于保存计算结果。`width`和`height`可视为要生成图片的水平方向的像素数量和竖直方向的像素数量
* 遍历每个像素，生成一条射线，调用`castRay()`方法，使其开始在场景里进行tracing，存储返回的颜色。生成Primary Ray的过程需要我们完成
* 将`framebuffer`的内容保存到图片中



### Scene

定义了要渲染的场景。

* 包含了一些必要的参数，如：

  * 相机渲染相关的`width`、`height`、`fov`等

  * 两个容器，用于保存场景中的物体和灯光信息

  * Ray Tracing 递归的最大深度

  * ……

* 一些必要的函数，如：
  * `void buildBVH()`：建立BVH加速结构
  * `Intersection intersect(const Ray& ray) const`：与scene的bvh求交
  * ……



### Ray

定义了一条射线，包含一条光的源头、方向、传递时间 t 和范围 range。

### OBJ_Loader

用于OBJ格式模型文件的导入。

### Material

将上个作业框架中Object类的材质参数拆分到了一个单独的类中，现在每个物体实例都可以拥有自己的材质。

### Intersection

定义了Ray和模型相交的交点的信息。



## Primary Ray的生成

可以直接使用我们上个作业中的实现（如果实现正确的话），也可以使用框架中为提前我们计算出来的x、y坐标。需要注意的是一些接口较上个作业框架有了改动，我们需要先创建一个Ray对象，再调用scene的castRay()方法：

```c++
Ray primary_ray{ eye_pos, dir };
framebuffer[m++] = scene.castRay(primary_ray, 0);
```



## Ray与三角形的求交判断

可以直接使用我们之前作业中的实现（如果实现正确的话），同时其实本次作业的框架依旧贴心地准备了实现：

```C++
Intersection inter;

if (dotProduct(ray.direction, normal) > 0)
    return inter;
double u, v, t_tmp = 0;
Vector3f pvec = crossProduct(ray.direction, e2);
double det = dotProduct(e1, pvec);
if (fabs(det) < EPSILON)
    return inter;

double det_inv = 1. / det;
Vector3f tvec = ray.origin - v0;
u = dotProduct(tvec, pvec) * det_inv;
if (u < 0 || u > 1)
    return inter;
Vector3f qvec = crossProduct(tvec, e1);
v = dotProduct(ray.direction, qvec) * det_inv;
if (v < 0 || u + v > 1)
    return inter;
t_tmp = dotProduct(e2, qvec) * det_inv;
```

这段代码的下半部分其实使用的就是Lecture 13中介绍的`Moller-Trumbore`方法，上半部分则额外考虑了射线射向三角形背面以及射线与三角形平行或共面的情况，但忽略了`t_tmp < 0`的情况。

此外，我们还需要获取相交物体的一些信息，用于Intersection对象的赋值。

相对于作业6，本次作业Intersection对象的成员变量有所增加，下面是每个成员变量的解释：

* happened：是否产生（符合要求的）交点
* coords：插值的顶点坐标
* tcoords：插值的纹理坐标
* normal：法线方向
* emit：材质的自发光颜色
* distance：射线的传播距离，即t值
* obj：指向交点所在Object的指针
* m：指向交点材质的指针



## Ray与Bounding Volume的求交判断

可以直接使用我们上个作业中的实现。

我们使用Lecture 13中的判断方法对Bounding Volume进行求交判断。实际上，这种方法的灵感来自于梁友栋-Barsky的线段裁剪算法。

![Liang-Barsky 算法](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw6_Liang-Barsky.png?raw=true)

分别取进入Bounding Volume的3个平面（较小t值）中的最大值，以及离开Bounding Volume的3个平面（较大t值）中的最小值，就可以得到直线在Bounding Volume中的部分。

由于Ray是射线，我们还需要保证离开平面的t值中的最小值大于0，这样才说明射线真正有存在于Bounding Volume中的部分。

注意检查 t_enter = t_exit 的时候的判断是否正确。



## BVH的查找过程

可以直接使用我们上个作业中的实现。整体思路：

* 创建一个Intersection对象，其中happened成员变量被初始化为false，表示没有交点
* 调用上面的方法，令Ray与当前Node的Bounding Volume进行求交，若没有交点，则直接返回
* 若当前Node的左右子结点都为空，则表示这个Node是叶子结点。因此，令Ray与该物体求交，返回交点
* 否则，该节点为中间结点，因此分别对其左右子节点递归调用getIntersection()函数，获得返回值，并取其中较近的交点返回



## 参考运行结果

![result](https://github.com/Orznijiang/My-Learn/blob/main/Games%20101/homework/Games101_Homework/Assignment_6/binary.png?raw=true)



## 参考链接

* 提高项-SAH划分：https://blog.csdn.net/ycrsw/article/details/124331686





fr出现负值

