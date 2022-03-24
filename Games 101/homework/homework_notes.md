# Games101 作业环境配置与思路理解

## Homework 0

作业0的内容主要是进行接下来的作业项目的环境配置。原本给的是一个已经配好环境的Ubuntu的虚拟机，装上就可以使用。我试着用那个环境写了前面几个作业，确实是挺好用的，省去了配置环境的麻烦。但奈何本人不太习惯使用Linux系统（菜），故还是尝试在Win10 + Visual Studio下配置环境，完成接下来的作业。

配置的过程中参考了一些文章，贴在下面。

由于课程中的要求，后面的作业只会分析实现的思路，不会给出源代码。

如有不对的地方，欢迎指正。

### 外部依赖库的配置

Games101作业使用的框架为`eigen3`和`opencv`。在Visual Studio中配置外部依赖库非常麻烦，这里使用了vcpkg来简化流程。

#### 1.安装vcpkg

可以直接使用git clone命令克隆一个当前版本。

```
git clone https://github.com/microsoft/vcpkg
//进行编译
.\vcpkg\bootstrap-vcpkg.bat
```

编译好以后会在同级目录下生成vcpkg.exe文件。编译期间，脚本会自动下载vswhere组件。

（不了解Git的同学可以进入上面命令的网址中下载zip包，在解压出来的目录中找到bootstrap-vcpkg.bat文件，双击运行）

#### 2.安装（下载和编译）开源库

利用vcpkg进行安装。

```
./vcpkg/vcpkg.exe install eigen3:x64-windows
./vcpkg/vcpkg.exe install opencv:x64-windows
```

#### 3.集成开源库

安装完开源库后，常规情况下，我们需要设置include目录、lib目录等，会有很多工作量。vcpkg提供了一套机制，可以全自动的适配目录，而开发者不需要关心已安装的库的目录在哪里，也不需要设置。这是vcpkg的一大优势。下面的命令将vcpkg安装的开源库集成到全局，“集成到全局”适用于Visual Studio开发环境和msbuild命令行。

```
./vcpkg/vcpkg.exe integrate install
```

当出现“Applied user-wide integration for this vcpkg root.”字样的时候，说明已经集成成功。这时候可以在任意的工程中使用安装好的第三方库。

### Visual Studio 中的配置

* 新建一个C++项目。
* 在项目-属性-配置属性-C/C++-语言-C++语言标准 中，选择C++17。据说是后面有使用到std::optional这个C++17特性。同时要使用x64平台。（项目中必须有C/C++代码才会出现C/C++这一栏）

![image-20220319212846663](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw0_c++17.png?raw=true "修改语言标准")

* 在项目-属性-配置属性-C/C++-预处理器-预处理器定义 中，加入`_CRT_SECURE_NO_WARNINGS`，消除某些警告。

![image-20220319213031478](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw0_define.png?raw=true "加入预处理器定义")

至此，就算是配置完成了。

### 参考链接

* https://zhuanlan.zhihu.com/p/360640432
* https://blog.csdn.net/cjmqas/article/details/79282847
* https://blog.csdn.net/cjmqas/article/details/79282847



## Homework 1

作业1的内容主要是将`get_model_matrix`和`get_projection_matrix`两个函数补充完整，通过使用正确的变换矩阵，最终能够在窗口绘制出一个三角形。

作业已经提供了基本的渲染程序框架，所以我们只需要在上面两个函数的实现中，返回正确的矩阵即可。关于矩阵变换的知识，主要集中在lecture_4。

在函数`get_view_matrix`中已经给出了观察矩阵的实现，将摄像机的位置简单地移动到原点。但是此时摄像机的方向是朝向+Z方向的（PPT中也讲到约定俗成的是让摄像机的方向朝向-Z方向），因此我在原本的基础上反转了Z轴（不是让摄像机绕Y轴旋转180度，这样X轴的坐标也会反转）这样三角形的几个顶点的Z值、`ZNear`、`ZFar`在观察坐标系下全部为正值，方便后面的计算

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

### 模型矩阵

作业的要求是实现绕着z轴的旋转，因此，可以直接应用z轴旋转的矩阵。

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_model_matrix.png?raw=true" alt="image-20220320191416537" title="绕Z轴旋转的矩阵公式" style="zoom:50%;" />

### 投影矩阵

首先，我们需要将透视投影矩阵的视锥体范围转换为正交投影矩阵的立方体范围，这在课程中已经有了详细的推导。

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_proj_matrix_1.png?raw=true" alt="image-20220320195727394" title="pers-ortho matrix" style="zoom:50%;" />

其中第三行的内容为`(0, 0, n+f, -nf)`。

将透视投影转换为正交投影后，剩下的工作就能够按照正交投影的方法快速解决了。

先将立方体的中心移动到原点，课程给出了矩阵：

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_proj_matrix_2.png?raw=true" alt="image-20220320200542929" title="ortho-trans matrix" style="zoom:50%;" />

由于摄像机本身在原点，所以X轴和Y轴的偏移其实是可以省略的。

然后，将立方体的取值范围缩放到[-1,1]：

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_proj_matrix_3.png?raw=true" alt="image-20220320201051061" title="ortho-scale matrix" style="zoom:50%;" />

上面是PPT中的缩放矩阵，PPT中的`n`和`f`都在-Z轴上，所以`n-f`大于0。由于我上面的操作，将`zNear`和`zFar`都变成正数，所以这里需要使用`f-n`，否则就会导致Z轴反转（此处不修改的话在这个作业中不会有问题，由于三角形是对称的，所以视觉效果是一样的，但在下一个深度测试的作业中，三角形的遮挡关系就会出错）

最后，将上述3个矩阵进行组合，就构成了投影矩阵。

### 运行结果参考

![image-20220320201343196](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_result.png?raw=true "result")



## Homework 2

作业2的主要内容是将一个三角形栅格化后显示到窗口上。

首先，需要将上个作业中对于投影矩阵的实现复制到 main.cpp 对应的函数中。

在`rasterize_triangle()`函数中，我们需要将传入的三角形参数`t`进行光栅化。阅读上面的代码可知，传入的三角形t的三个点的坐标是已经经过MVP矩阵变换且经过齐次除法和屏幕坐标变换的（后面计算插值的深度值时又做了一次齐次除法，但此时`w`值已经是1了，个人感觉多此一举了）。

### 光栅化

首先，我们根据三角形的3个顶点计算出2维的包围盒来减少遍历的像素数量。

注意：

* 只需要计算2维，也就是x和y的最大值和最小值，因为我们遍历的像素是2维的。
* 在计算出最大值和最小值时，不能直接使用，而是使用`floor()`函数计算像素的索引值

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_aabb.png?raw=true" title="bouding box" style="zoom:50%;" />

然后遍历上面计算的包围盒，对每一个像素索引，计算像素的中心坐标，使用中心坐标去判断该像素是否位于三角形的内部。

中心坐标的示意图：

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_center_point.png?raw=true" alt="image-20220324030650798" title="center point" style="zoom:50%;" />

关于如何判断像素是否在三角形的内部，Lecture_06给出了一个方法，就是使用叉乘来判断该像素是否位于三角形的三条边的同一侧（左边或是右边）。我们需要在函数`insideTriangle(float x, float y, const Vector3f* _v)`中进行实现。

注意：

* 测试了一下，发现Eigen库中好像只支持3维向量的叉乘。为了保证叉乘结果的准确性，需要手动将每个向量的第3维置为0（相当于放在了3维空间的同一个平面上）
  * 这样计算出来的结果，有2维肯定是0
  * 我们只需要关注非0的那一个结果
    * 它的值即为向量中4个非0值组成的行列式的值
    * 这个值是有方向的，也就是说，它可能是正的，也可能是负的
    * 当像素对三角形的三条边所形成的的向量进行叉乘，得到的结果的方向相同时（即同为正或负），说明该像素在三角形的内部
* 三角形三个向量以及像素与三角形顶点的向量必须按照一定顺序进行声明，如AB、BC、CA（而不是AB、BC、AC）

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_cross_test.png?raw=true" title="叉乘判断法" style="zoom: 50%;" />

### 深度测试

确定了该像素在三角形内部之后，我们就需要知道三角形在该点的深度值。

三角形的3个顶点的深度值（即z值）是已知的，我们需要通过插值来得到该点的深度值（实际上，由于两个给定的三角形都平行于XY平面，Z值在三角形上完全相等，不需要插值也能完成，但是计算插值深度是更通用的步骤）

课程中涉及三角形插值方面的内容在Lecture_09，而作业2在前面几讲就放出来了。下面会给出一个这方面内容的介绍链接，或者可以选择看完Lecture_09再完成作业2。考虑到这方面内容的暂时性缺失，作业2给的代码中已经给出了这方面的实现，不需要自己去写。但是给出的源码个人感觉还有可以优化的地方：

* 在光栅化之前，已经对三角形的3个顶点进行了齐次除法，顶点的`w`项已经为1，这里再除以1没有任何意义，可以直接删除
* 三角形重心坐标的三项`alpha,beta,gamma`之和必为1。因此算法中的`w_reciprocal`项存在与否也是无所谓的
* 因此，插值的深度值只是简单的3个点的z值与对应的重心坐标的加权和，即：`float z_interpolated = alpha * v[0].z() + beta * v[1].z() + gamma * v[2].z();`

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



### 运行结果参考

![image-20220324194759716](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw2_result.png?raw=true "result")

### 提高项实现思路

本人比较懒，没有写提高项，在这里就写写实现的思路。并且我上面运行的结果并没有出现不正常的黑边，也就感觉没有必要去解决了（笑）

* 由于需要进行2x2的采样，我们要额外创建原来4倍大小的buffer（包括color和depth）
* 在遍历像素索引时，不再使用像素中心坐标，而是使用将像素分成4个子像素后的中心坐标，即`(x + 0.25, y + 0.25)`、`(x + 0.25, y + 0.75)`、`(x + 0.75, y + 0.25)`、`(x + 0.75, y + 0.75)`
* 对于每一个采样点，若处于三角形内部且插值后的深度值小于深度缓冲中的深度，就更新颜色缓冲中的信息
* 完成遍历（所有三角形）后，对2x2的采样结果进行平均，放到原来的颜色缓冲中，得到最终的结果

