# Homework 2

作业2的主要内容是将一个三角形光栅化后显示到窗口上。

首先，需要将上个作业中对于投影矩阵的实现复制到 main.cpp 对应的函数中。

在`rasterize_triangle()`函数中，我们需要将传入的三角形参数`t`进行光栅化。阅读上面的代码可知，传入的三角形t的三个点的坐标是已经经过MVP矩阵变换且经过齐次除法和屏幕坐标变换的（后面计算插值的深度值时又做了一次齐次除法，但此时`w`值已经是1了，个人感觉多此一举了）。

## 光栅化

首先，我们根据三角形的3个顶点计算出2维的包围盒来减少遍历的像素数量。

注意：

* 只需要计算2维，也就是x和y的最大值和最小值，因为我们遍历的像素是2维的。
* 在计算出最大值和最小值时，不能直接使用，而是使用`floor()`函数计算像素的索引值

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_aabb.png?raw=true" alt="bouding box" title="bouding box" style="zoom:50%;" />

然后遍历上面计算的包围盒，对每一个像素索引，计算像素的中心坐标，使用中心坐标去判断该像素是否位于三角形的内部。

中心坐标的示意图：

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_center_point.png?raw=true" alt="center point" title="center point" style="zoom:50%;" />

关于如何判断像素是否在三角形的内部，Lecture_06给出了一个方法，就是使用叉乘来判断该像素是否位于三角形的三条边的同一侧（左边或是右边）。我们需要在函数`insideTriangle(float x, float y, const Vector3f* _v)`中进行实现。

注意：

* 测试了一下，发现Eigen库中好像只支持3维向量的叉乘。为了保证叉乘结果的准确性，需要手动将每个向量的第3维置为0（相当于放在了3维空间的同一个平面上）
  * 这样计算出来的结果，有2维肯定是0
  * 我们只需要关注非0的那一个结果
    * 它的值即为向量中4个非0值组成的行列式的值
    * 这个值是有方向的，也就是说，它可能是正的，也可能是负的
    * 当像素对三角形的三条边所形成的的向量进行叉乘，得到的结果的方向相同时（即同为正或负），说明该像素在三角形的内部
* 三角形三个向量以及像素与三角形顶点的向量必须按照一定顺序进行声明，如AB、BC、CA（而不是AB、BC、AC）

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_cross_test.png?raw=true" alt="叉乘判断法" title="叉乘判断法" style="zoom: 50%;" />

## 深度测试

确定了该像素在三角形内部之后，我们就需要知道三角形在该点的深度值。

三角形的3个顶点的深度值（即z值）是已知的，我们需要通过插值来得到该点的深度值（实际上，由于两个给定的三角形都平行于XY平面，Z值在三角形上完全相等，不需要插值也能完成，但是计算插值深度是更通用的步骤）

课程中涉及三角形插值方面的内容在Lecture_09，而作业2在前面几讲就放出来了。下面会给出一些这方面内容的介绍链接，或者可以选择看完Lecture_09再完成作业2。考虑到这方面内容的暂时性缺失，作业2给的代码中已经给出了这方面的实现，不需要自己去写。但是给出的源码个人感觉还有可以优化的地方：

* 在光栅化之前，已经对三角形的3个顶点进行了齐次除法，顶点的`w`项已经为1，这里再除以1没有任何意义，可以直接删除

* 三角形重心坐标的三项`alpha,beta,gamma`之和必为1。因此算法中的`w_reciprocal`项存在与否也是无所谓的

* 因此，插值的深度值只是屏幕空间下的3个点的z值与对应的重心坐标的加权和，即：`float z_interpolated = alpha * v[0].z() + beta * v[1].z() + gamma * v[2].z();`

  * 在这个作业中，这样的结果是恰好正确的，因为三角形都平行于XY平面，z值完全相同，所以投影后重心坐标不发生改变

  * 然而，在透视投影变换中，当三角形顶点的z值不完全相同时，其上某一点的重心坐标与投影后的三角形的对应点的重心坐标不一定相同，导致上面这个加权和插值出的深度与这个点真正的深度不一致（具体的原因也可以参考下面的链接）

  * 在实际的应用中，我们不应该直接使用上面屏幕空间下计算出来的插值结果，而是要将这个插值结果进行校正，得到真正的在三维空间下的准确的插值结果，下面给出公式，推导过程可看下面的参考链接

    ![correction1](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_recorrect1.png?raw=true "correction1")

    ![recorrection2](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_recorrect2.png?raw=true "recorrection2")

    * 其中，A、B、C为三角形的三个点，P表示要插值的点，Z表示投影变换前各点的深度值，而α、β、γ表示重心坐标，其中带有`'`的表示在屏幕空间的重心坐标，不带`'`的表示在投影变换前的重心坐标

    * 由于之前的齐次除法将w分量也进行了除法操作，导致w分量恒为1。否则，就可以保留Z值用作后面的深度插值校正

  * 同时，在进行真正的深度测试时也不会使用线性的深度值，而是希望近处的深度值拥有更大的精度。所以，顶点的深度值会经过一定的处理，但是插值还是线性的
  
  * 经验证，在本例中校正前后的深度值确实差别不大
  
    ![校正前后深度值对比](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_correction_vs.png?raw=true)

注意：

* 源码中计算重心坐标的语句：`auto [alpha, beta, gamma] = computeBarycentric2D(x, y, t.v);`其中用中括号`[alpha, beta, gamma]`的方式是C++的新特性，需要像之前配置环境时讲到的将C++的语言标准设置为C++17。



**说到三角形的重心坐标，实际上我们可以直接使用三角形的重心坐标来判断点是否位于三角形的内部：**

* 若`alpha`、`beta`、`gamma`的值全部大于0，说明点在三角形内部
* 若`alpha`、`beta`、`gamma`的值1个等于0，2个大于0，说明点在三角形上
* 若`alpha`、`beta`、`gamma`的存在值小于0，说明点在三角形外部
* 由于重心坐标之和为1，所以若有1项大于1，则点必在三角形外部

因此，我们可以直接简化掉叉乘的计算，使用插值同时判断点是否在三角形内部以及进行插值，简化计算。



得到插值深度值之后，将深度值与当前深度缓冲中的深度值进行比较，若发现当前的深度值小于缓冲中的深度值，则表示当前三角形内部的该像素点在最前面。因此，需要将该点的颜色设置为该三角形的颜色。

注意：

* 若发现需要更新帧缓冲的颜色，在之后必须更新深度缓冲中的内容，否则深度永远是最大值，后面绘制的永远会在最上面显示



## 运行结果参考

![result](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_result.png?raw=true "result")

## 提高项实现思路

本人比较懒，没有写提高项，在这里就写写实现的思路。并且我上面运行的结果并没有出现不正常的黑边，也就感觉没有必要去解决了（笑）

* 由于需要进行2x2的采样，我们要额外创建原来4倍大小的buffer（包括color和depth）
* 在遍历像素索引时，不再使用像素中心坐标，而是使用将像素分成4个子像素后的中心坐标，即`(x + 0.25, y + 0.25)`、`(x + 0.25, y + 0.75)`、`(x + 0.75, y + 0.25)`、`(x + 0.75, y + 0.75)`
* 对于每一个采样点，若处于三角形内部且插值后的深度值小于深度缓冲中的深度，就更新颜色缓冲中的信息
* 完成遍历（所有三角形）后，对2x2的采样结果进行平均，放到原来的颜色缓冲中，得到最终的结果

## 参考链接

* https://blog.csdn.net/weixin_35968185/article/details/112720041
* https://blog.csdn.net/wangjiangrong/article/details/115326930
* https://blog.csdn.net/wangjiangrong/article/details/107770259
* https://zhuanlan.zhihu.com/p/400257532
* https://www.cnblogs.com/mikewolf2002/archive/2012/11/25/2787480.html
* https://zhuanlan.zhihu.com/p/380589244
* https://blog.csdn.net/qq_18998145/article/details/117222382

