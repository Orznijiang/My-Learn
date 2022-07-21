# Homework 7

之前的作业实现了 Whitted-Style Ray Tracing 算法，并且用 BVH 等加速结构对于求交过程进行了加速。作业7将在上一次实验的基础上（保留BVH加速结构）实现完整的 Path Tracing 算法。该部分的知识集中在Lecture 15和Lecture 16中。

作业框架已经为我们提供了大部分的实现，包括BVH结构的递归构建、采样方法、pdf计算以及BRDF系数计算的具体实现。在理解框架的大部分实现后，我们所需要补充的代码仅为 Path Tracing 算法过程中对每条射线Ray的递归处理过程，即`castRay(const Ray &ray, int depth)`函数。同时需要迁移上个作业中自己实现的代码。

首先，或许需要修改模型文件的读取路径，取决于你的放置位置：

```c++
MeshTriangle floor("models/cornellbox/floor.obj", white);
MeshTriangle shortbox("models/cornellbox/shortbox.obj", white);
MeshTriangle tallbox("models/cornellbox/tallbox.obj", white);
MeshTriangle left("models/cornellbox/left.obj", red);
MeshTriangle right("models/cornellbox/right.obj", green);
MeshTriangle light_("models/cornellbox/light.obj", light);
```

注意到，这次的作业框架将光源视为Object，而不是使用单独的光源对象。我们后面需要根据Object材质的自发光属性来判断求交的结果是否是光源，即：

```c++
intersection.m->hasEmission();
```



## 代码分析

由于本次作业框架与上次作业框架高度重合，这里仅对增加的且使用到或者有修改的部分进行解释。重复的代码分析参考上一篇文章。

### Material

每个物体实例都可以拥有自己的材质对象成员。

成员变量分析：

* m_type：表示材质的类型。在本次作业中，仅有一种材质类型，即漫反射：

```C++
enum MaterialType { DIFFUSE};
```

* m_emission：描述材质的自发光属性，可以使用`hasEmission()`函数判断这个成员变量的值是否不为0，若是则说明在本作业框架中这是一个光源

成员函数分析：

* `toWorld(const Vector3f &a, const Vector3f &N)`：字面意思上理解，是将传入的向量a转换到世界坐标系下。实际上，我们认为作业框架中的法线方向（N）都是默认处于世界坐标系下的，该方法以向量N为基础，计算出一对与N垂直且相互正交的向量用作正交基（与作业3中tbn矩阵的思想一样）。此时，这3个向量的坐标即为从 **由这3个向量组成的空间** 转换到 **世界空间** 后这三个基向量在 **世界空间** 中的位置。使用这3个向量组成的矩阵对某个向量进行变换，就是将这个向量的坐标看作原本处于 **这三个基向量组成的空间** 中，然后对其进行变换，将其变换到 **世界空间** 中的对应坐标，即：`return a.x * B + a.y * C + a.z * N;`

```c++
Vector3f B, C;
if (std::fabs(N.x) > std::fabs(N.y)){
    float invLen = 1.0f / std::sqrt(N.x * N.x + N.z * N.z);
    C = Vector3f(N.z * invLen, 0.0f, -N.x *invLen);
}
else {
    float invLen = 1.0f / std::sqrt(N.y * N.y + N.z * N.z);
    C = Vector3f(0.0f, N.z * invLen, -N.y *invLen);
}
B = crossProduct(C, N);
return a.x * B + a.y * C + a.z * N;
```

* `sample(const Vector3f &wi, const Vector3f &N)`：按照材质的性质，给定入射方向与法向量，用某种分布采样一个出射方向。由于场景中仅存在漫反射材质，出射方向即为在半球上随机进行采样。其中`get_random_float()`函数返回一个0~1之间的浮点值。
  * 生成2个0~1的随机数x1，x2
  * 根据x1计算z分量，为-1~1之间的随机浮点值
  * 根据z值以及总长度（1）计算出另外2个分量的平方和的根
  * 根据x2计算弧度phi，范围为0~2π，即为一个圆的弧度
  * 根据phi值即平方和的根计算剩下2个分量
  * 调用上面的`toWorld()`函数，得到世界空间下的采样方向

```c++
// uniform sample on the hemisphere
float x_1 = get_random_float(), x_2 = get_random_float();
float z = std::fabs(1.0f - 2.0f * x_1);
float r = std::sqrt(1.0f - z * z), phi = 2 * M_PI * x_2;
Vector3f localRay(r*std::cos(phi), r*std::sin(phi), z);
return toWorld(localRay, N);
```

* `pdf(const Vector3f &wi, const Vector3f &wo, const Vector3f &N)`：给定一对入射、出射方向与法向量，计算 sample 方法得到该出射方向的概率密度。由于场景中仅存在漫反射材质，sample方法为在半球上均匀采样，则可以计算出pdf值即为1/半球的面积，相关理论可参考Lecture 15

```c++
// uniform sample probability 1 / (2 * PI)
if (dotProduct(wo, N) > 0.0f)
    return 0.5f / M_PI;
else
    return 0.0f;
break;
```

* `eval(const Vector3f &wi, const Vector3f &wo, const Vector3f &N)`：给定一对入射、出射方向与法向量，计算这种情况下的 f_r 值。由于场景中仅存在漫反射材质，该材质的 f_r 值为Kd/π，引入1/π是为了保证能量的守恒，具体的推导过程可参考Lecture 17

![f_r_diffuse](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw7_f_r_diffuse.png?raw=true)



### Scene

定义了要渲染的场景。

* 包含了一些必要的参数，如：

  * 相机渲染相关的`width`、`height`、`fov`等

  * 两个容器，用于保存场景中的物体和灯光信息。实际上本次作业框架中将灯光也当做一个物体来处理

  * Ray Tracing 递归的最大深度

  * 新增：俄罗斯轮盘（RussianRoulette）的概率

  * ……

* 一些必要的函数，如：
  * `void buildBVH()`：建立BVH加速结构
  * `Intersection intersect(const Ray& ray) const`：与scene的bvh求交
  * ……

* `sampleLight(Intersection &pos, float &pdf) const`：在场景的所有光源上按面积 uniform 地 sample 一个点，并计算该 sample 的概率密度。算法首先遍历场景中的所有光源（实际上场景中只有一个光源）并计算出光源面积的和，然后使用随机数的方法取到一个随机的光源，对这个光源进行采样。即，随机取到该光源上的一个点，返回Intersection信息，并计算pdf概率密度的值（面积的倒数）：

  ```c++
  float emit_area_sum = 0;
  for (uint32_t k = 0; k < objects.size(); ++k) {
      if (objects[k]->hasEmit()){
          emit_area_sum += objects[k]->getArea();
      }
  }
  float p = get_random_float() * emit_area_sum;
  emit_area_sum = 0;
  for (uint32_t k = 0; k < objects.size(); ++k) {
      if (objects[k]->hasEmit()){
          emit_area_sum += objects[k]->getArea();
          if (p <= emit_area_sum){
              objects[k]->Sample(pos, pdf);
              break;
          }
      }
  }
  ```

    * 需要注意的是，对于MeshTriangle对象的采样，会使用到BVH的加速。由于对里面的单个三角形进行采样时会将pdf设置为该三角形面积的倒数，而对MeshTriangle对象来说正确的是整体面积的倒数，所以BVH的Node存储了该Node的面积，以抵消单个三角形进行采样时对pdf值的修改

    * 此外，在采样时对部分随机数做了根号处理，我不是十分理解，懂的老哥可以解答下：

      ```C++
      // BVHAccel::Sample(Intersection &pos, float &pdf)
      float p = std::sqrt(get_random_float()) * root->area;
      
      // Triangle::Sample(Intersection &pos, float &pdf)
      float x = std::sqrt(get_random_float()), y = get_random_float();
      pos.coords = v0 * (1.0f - x) + v1 * (x * (1.0f - y)) + v2 * (x * y);




### global

定义了整个框架会用到的一些基本函数和变量。

`get_random_float()`：用于生成0~1的随机浮点数。由于每次调用都会创建临时的变量，然后又销毁，而这个函数被调用的次数又特别巨大，因此造成了很大的性能损失。可以将变量修改为静态类型，放在函数外部，内部直接调用，这样就不用重复地创建和销毁：

```c++
static std::random_device dev;
static std::mt19937 rng(dev());
static std::uniform_real_distribution<float> dist(0.f, 1.f);

inline float get_random_float()
{
    return dist(rng);
}
```



### Intersection

定义了Ray和模型相交的交点的信息。

相对于作业6，本次作业Intersection对象的成员变量有所增加，下面是每个成员变量的解释：

* happened：是否产生（符合要求的）交点
* coords：插值的顶点坐标
* tcoords：插值的纹理坐标
* normal：法线方向
* emit：材质的自发光颜色
* distance：射线的传播距离，即t值
* obj：指向交点所在Object的指针
* m：指向交点材质的指针



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



## Ray与Bounding Volume的求交判断

可以直接使用我们上个作业中的实现。

我们使用Lecture 13中的判断方法对Bounding Volume进行求交判断。实际上，这种方法的灵感来自于梁友栋-Barsky的线段裁剪算法。

![Liang-Barsky 算法](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw6_Liang-Barsky.png?raw=true)

分别取进入Bounding Volume的3个平面（较小t值）中的最大值，以及离开Bounding Volume的3个平面（较大t值）中的最小值，就可以得到直线在Bounding Volume中的部分。

由于Ray是射线，我们还需要保证离开平面的t值中的最小值大于0，这样才说明射线真正有存在于Bounding Volume中的部分。

注意检查 t_enter = t_exit 的时候的判断是否正确。由于场景中部分三角形（比如光源）的平面完全与某个轴垂直，这会导致其AABB在某个轴上的最小值和最大值相等，因此计算出的t_enter = t_exit也可能相等。在这个作业中，我们需要将相等的情况视为存在交点。



## BVH的查找过程

可以直接使用我们上个作业中的实现。整体思路：

* 创建一个Intersection对象，其中happened成员变量被初始化为false，表示没有交点
* 调用上面的方法，令Ray与当前Node的Bounding Volume进行求交，若没有交点，则直接返回
* 若当前Node的左右子结点都为空，则表示这个Node是叶子结点。因此，令Ray与该物体求交，返回交点
* 否则，该节点为中间结点，因此分别对其左右子节点递归调用getIntersection()函数，获得返回值，并取其中较近的交点返回



## Path Tracing 过程的递归实现

根据Lecture 16以及作业文档中给出的伪代码，可以较容易地写出 Path Tracing 算法的过程，下面简要讲述流程，并指出需要注意的点：

* 首先，令Ray与场景中的物体求交，得到交点intersection

* 若存在交点

  * 判断交点处是否为光源，由于光源也是一个Object对象，因此需要判断其是否有emission属性。若我们的primary ray直射到了光源（即depth = 0），则表示由摄像机可直接看到光源，因此直接返回光源颜色

    ```
    if (mat->hasEmission() && depth == 0) {
        return mat->getEmission();
    }
    ```

    实际上不需要判断depth的值，因为除了primary ray的求交，后面的ray在递归调用castRay之前，都会提前判断该ray是否与光源相交，若与光源相交则停止tracing，因此后面的ray不会再与光源相交。

  * 尝试计算L_dir：

    调用`sampleLight()`函数对光源进行采样，得到光源上随机一点x的信息和概率密度函数值

    * 创建一条从交点p射向光源点x的射线，判断交点是否为光源
      * 若不是光源，则说明光源被其他物体挡住，无法照亮交点p
      * 若未被挡住，则计算各种量，得到直接光的L值
        * f_r：`mat->eval(wo, -ws, N)`
        * cosθ：`saturate(dotProduct(N, -ws))`
        * cosθ‘：`saturate(dotProduct(NN, ws))`
        * distance^2^：`pow((x - p).norm(), 2)`
        * L_dir：`light_pos.emit * f_r * cos_theta * cos_theta_prime / distance2 / light_pdf`
        * 其中p表示射线交点，wo表示射线方向（view to p），ws表示光源方向（light to p），N表示交点的法线方向，x表示光源上采样到的点的位置，NN表示光源上x点的法线方向
        * 有几点需要注意：
          * ws的方向，计算cosθ时以交点p为基准点，而计算cosθ‘时以光源上的点x为基准点，二者计算时的ws方向相反
          * 对于cos值的计算，要确保结果大于或等于0，因为不能从背面照亮物体

  * 尝试计算L_indir：

    调用`get_random_float()`函数获得一个0~1的随机数，与Scene::RussianRoulette进行比较

    * 若未通过比较，则不投射光线
    * 若通过了比较，则
      * 对半球进行采样得到一个随机方向wi（漫反射均匀分布）
      * 调用`intersect()`函数对场景中的物体进行求交
      * 若交点不是光源，才继续进行计算
        * 对上面的方向，递归调用`castRay()`函数，得到返回值
        * 计算f_r：`mat->eval(wo, wi, N)`
        * 计算cos_theta：`saturate(dotProduct(N, wi))`
        * 计算pdf：`mat->pdf(wo, wi, N)`
        * 计算L_indir：`castRay(Ray(p, wi), depth + 1) * f_r * cos_theta / pdf / Scene::RussianRoulette`

  * 返回`L_dir + L_indir`





## 参考运行结果

ssp=16：

![binary16](https://github.com/Orznijiang/My-Learn/blob/main/Games%20101/homework/Games101_Homework/Assignment_7/binary16.png?raw=true)



ssp=256：

![binary256](https://github.com/Orznijiang/My-Learn/blob/main/Games%20101/homework/Games101_Homework/Assignment_7/binary256.png?raw=true)



## 参考链接

* https://blog.csdn.net/weixin_43485513/article/details/122779134?spm=1001.2014.3001.5506
* https://blog.csdn.net/qq_41835314/article/details/125166417?spm=1001.2101.3001.6650
