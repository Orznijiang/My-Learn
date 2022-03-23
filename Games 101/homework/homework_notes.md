# Games101 作业环境配置与思路理解

## Homework 0

作业0的内容主要是进行接下来的作业项目的环境配置。原本给的是一个已经配好环境的Ubuntu的虚拟机，装上就可以使用。我试着用那个环境写了前面几个作业，确实是挺好用的，省去了配置环境的麻烦。但奈何本人不太习惯使用Linux系统（菜），故还是尝试在Win10 + Visual Studio下配置环境，完成接下来的作业。

配置的过程中参考了一些文章，贴在下面。

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

在函数`get_view_matrix`中已经给出了观察矩阵的实现，可以看到，默认是认为摄像机朝向-Z方向，所以只需要将摄像机的位置移动到原点（实际上，若摄像机默认不朝着-Z方向会更麻烦，不过课程中也有讲到，估计是为了降低第一个作业的难度）。我们可以根据这个函数的实现完成剩余矩阵的补充。

```
Eigen::Matrix4f translate;
translate << 1, 0, 0, -eye_pos[0], 
			 0, 1, 0, -eye_pos[1], 
			 0, 0, 1, -eye_pos[2],、
             0, 0, 0, 1;
```

### 模型矩阵

作业的要求是实现绕着z轴的旋转，因此，可以直接应用z轴旋转的矩阵。

![image-20220320191416537](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_model_matrix.png?raw=true "绕Z轴旋转的矩阵公式")

### 投影矩阵

首先，我们需要将透视投影矩阵的视锥体范围转换为正交投影矩阵的立方体范围，这在课程中已经有了详细的推导。

![image-20220320195727394](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_proj_matrix_1.png?raw=true "pers-ortho matrix")

其中第三行的内容为`(0, 0, n+f, -nf)`。

这里有一点需要注意，由于观察矩阵使得摄像机朝向-Z方向，此时观察坐标系和世界坐标系的Z轴方向是相反的，因此需要将Z值取反，由于我们不能修改观察矩阵，这里直接将矩阵的（4,3）修改为-1也能起到同样的效果。

将透视投影转换为正交投影后，剩下的工作就能够按照正交投影的方法快速解决了。

先将立方体的中心移动到原点，课程给出了矩阵：

![image-20220320200542929](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_proj_matrix_2.png?raw=true "ortho-trans matrix")

由于摄像机本身在原点，所以X轴和Y轴的偏移其实是可以省略的。

然后，将立方体的取值范围缩放到[-1,1]：

![image-20220320201051061](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_proj_matrix_3.png?raw=true "ortho-scale matrix")

最后，将上述3个矩阵进行组合，就构成了投影矩阵。

### 运行结果参考

![image-20220320201343196](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw1_result.png?raw=true "result")



## Homework 2

作业2的主要内容是将一个三角形栅格化后显示到窗口上。

首先，将上个作业中对于投影矩阵的实现复制到 main.cpp 下的 get_projection_matrix() 函数中。

在rasterize_triangle()函数中，我们需要将传入的三角形参数t进行光栅化。阅读上面的代码可知，传入的三角形t的三个点的坐标是已经经过MVP矩阵变换且经过齐次除法和屏幕坐标变换的。

c++17 [alpha,beta,gamma]

cross[a,b]
