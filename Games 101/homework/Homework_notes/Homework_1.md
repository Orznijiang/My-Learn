# Homework 1

作业1的内容主要是将`get_model_matrix`和`get_projection_matrix`两个函数补充完整，通过使用正确的变换矩阵，最终能够在窗口绘制出一个三角形。

作业已经提供了基本的渲染程序框架，所以我们只需要在上面两个函数的实现中，返回正确的矩阵即可。关于矩阵变换的知识，主要集中在lecture_4。

在函数`get_view_matrix`中已经给出了观察矩阵的实现，将摄像机的位置简单地移动到原点。课程PPT中讲到约定俗成的是让摄像机的方向朝向-Z方向，我将其理解为看向世界空间中的-Z方向，在以摄像机为原点的观察坐标系中，我反转Z轴（不是让摄像机绕Y轴旋转180度，这样X轴的坐标也会反转）使得三角形的几个顶点的Z值、`ZNear`、`ZFar`在观察坐标系下全部为正值，方便后面的计算（否则后面齐次除法的Z值需要修改为-Z值）

```
Eigen::Matrix4f translate;
translate << 1, 0, 0, -eye_pos[0], 
			 0, 1, 0, -eye_pos[1], 
			 0, 0, 1, -eye_pos[2],、
             0, 0, 0, 1;
Eigen::Matrix4f inverse;
inverse << 1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, -1, 0,
           0, 0, 0, 1;
```

## 模型矩阵

作业的要求是实现绕着Z轴的旋转，因此，可以直接应用Z轴旋转的矩阵。

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_model_matrix.png?raw=true" alt="绕Z轴旋转的矩阵公式" title="绕Z轴旋转的矩阵公式" style="zoom:50%;" />

## 投影矩阵

首先，我们需要将透视投影矩阵的视锥体范围转换为正交投影矩阵的立方体范围，这在课程中已经有了详细的推导。

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_proj_matrix_1.png?raw=true" alt="pers-ortho matrix" title="pers-ortho matrix" style="zoom:50%;" />

其中第三行的内容为`(0, 0, n+f, -nf)`。

将透视投影转换为正交投影后，剩下的工作就能够按照正交投影的方法快速解决了。

先将立方体的中心移动到原点，课程给出了矩阵：

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_proj_matrix_2.png?raw=true" alt="ortho-trans matrix" title="ortho-trans matrix" style="zoom:50%;" />

由于摄像机本身在原点，所以X轴和Y轴的偏移其实是可以省略的。

然后，将立方体的取值范围缩放到[-1,1]：

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_proj_matrix_3.png?raw=true" alt="ortho-scale matrix" title="ortho-scale matrix" style="zoom:50%;" />

上面是PPT中的缩放矩阵，PPT中的`n`和`f`都在-Z轴上，所以`n-f`大于0。由于我上面的操作，将`zNear`和`zFar`都变成正数，所以这里需要使用`f-n`，否则就会导致Z轴反转（此处不修改的话在这个作业中不会有问题，由于三角形是对称的，所以视觉效果是一样的，但在下一个深度测试的作业中，三角形的遮挡关系就会出错）

最后，将上述3个矩阵进行组合，就构成了投影矩阵。

### 运行结果参考

![运行结果](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_result.png?raw=true "result")