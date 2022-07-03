# Homework 4

作业4的主要内容是实现递归的贝塞尔曲线绘制。

这次的作业比较简单，相比作业3的代码量少了很多。



## 贝赛尔曲线的递归实现

作业框架中已经实现了多项式方程控制的3阶贝赛尔曲线的绘制，即对于一个t值，直接利用公式计算出其曲线的坐标位置。
$$
b^n(t) = \sum^n_{j=0}b_jB^n_j(t)
$$

$$
B^n_i(t) = \begin{pmatrix} n \\ i \\ \end{pmatrix}t^i(1-t)^{n-i}
$$



我们要实现的是递归的贝赛尔曲线计算，以4个控制点的3阶贝塞尔曲线为例，根据t值在4个控制点形成的3条线段上进行采样，得到3个插值点。再根据t值在这3个插值点形成的2条线段上进行采样，得到2个新的插值点……最终的插值点即为贝赛尔曲线在当前t值下的位置。

![贝塞尔曲线递归插值示意图](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw4_bezier.png?raw=true)

关于递归和多项式方程的贝塞尔曲线实现过程，在Lecture 11中有详细介绍。

在`recursive_bezier()`函数中，我们在每次调用时对其容器中的所有的n个顶点进行一次插值，得到n-1个顶点，若插值后的顶点数量不为1，则递归调用该函数，直到剩余1个顶点，返回该顶点的位置。

```c++
if (points.size() != 1) {
    return recursive_bezier(points, t);
}
else {
    return points[0];
}
```

在函数`bezier()`中，我们使用类似`naive_bezier()`的方法，使用多个不同的t值调用我们实现的`recursive_bezier()`函数，以生成完整的贝塞尔曲线。

为了与原实现区分，我们需要修改自己的实现生成的曲线的颜色，即设置对应位置点的颜色。

```
window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
```

上面将（x，y）位置的R（red）分量设置为255。可见 [1] 控制G（green）分量，[0] 控制B（blue）分量。



## 运行结果参考

将我们自己的实现生成的曲线颜色设置为绿色，同时开启原实现的绘制，可以得到黄色的混合结果：

![result](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw4_bezier_result.png?raw=true)