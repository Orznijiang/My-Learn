# Homework 3

作业3的主要内容是将一个可爱的牛牛模型渲染到屏幕上，并添加各种渲染效果。本次作业的坑比较多，文档表述也不太清楚，建议不要一个人硬写。

## 前期准备

* 首先，将之前作业中的观察矩阵和投影矩阵的实现复制到`main.cpp`对应的函数中
* 根据`models`文件夹放置的具体位置，修改`main`函数中的`obj_path`路径
* 同样，根据实际情况修改`LoadFile()`函数中的路径，读取模型文件错误时会在窗口输出错误信息

本人之前作业中的变换矩阵在这次作业中不再完全适用。这是因为，作业中只对模型顶点进行MVP矩阵的变换，并且将normal信息变换到了观察空间中，我这里假定观察空间正向是正Z轴，而作业框架中假定看向-Z轴，这会导致法线在观察空间下的z值不一致。同时，作业框架中直接给出假定摄像机在观察空间中看向Z轴的情况下的光源坐标位置，与我的假定情况不一致，这也会导致光源方向的不一致。要得到与作业结果一致的渲染图，需要在我之前作业的矩阵的基础上做出下述修改：

* 在观察矩阵中，不再反转Z轴

* 在$M_{persp \rightarrow ortho}$矩阵中，使投影后的w值为-z（因为z小于0），即修改最后一排为-1：
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

此外，`rasterize_triangle()`函数的参数列表也进行了更新，`t.v`成员修改为`Eigen::Vector4f`以传入`v`值，同时`Triangle`也传入了除顶点信息以外的其他信息；`view_pos`成员主要给出观察空间下的顶点位置，因为我们后面的光照计算全是在观察空间下进行的（这也是为什么之前的矩阵需要修改）。



auto getInterpolateResult = [&](auto& propA, auto& propB, auto& propC) -> auto {
                    return Z * (alpha * propA / v[0].w() + beta * propB / v[1].w() + gamma * propC / v[2].w());
                };

在c++20以前，不可以用Lambda 表达式捕获结构化绑定。



![image-20220701162552260](E:\My Documents\Github\MyImageBed\My-Learn\Games 101\homework\homework_notes\hw3_error1.png)

set_pixel(Eigen::Vector3f(i, j, zp), Eigen::Vector3f(0,0,0));

![image-20220701210113735](E:\My Documents\Github\MyImageBed\My-Learn\Games 101\homework\homework_notes\hw3_error2.png)

Eigen::Vector3f deot = kd.cwiseProduct(light.intensity);



normalize()

normalized()



float u = payload.tex_coords.x() - floor(payload.tex_coords.x());
        float v = payload.tex_coords.y() - floor(payload.tex_coords.y());





auto b = n.cross(t);
    auto tex_height = payloa



 1.0f / tex_width, v

焯



auto displace_pos = payload.view_pos + kn * n * payload.texture->getColor(u, v).norm();

焯



## 参考链接

* https://blog.csdn.net/fpcc/article/details/121992645
* https://blog.csdn.net/qq_45065475/article/details/105906539
* 作业2：https://zhuanlan.zhihu.com/p/535088979