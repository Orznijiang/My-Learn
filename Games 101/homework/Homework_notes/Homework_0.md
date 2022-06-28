# Homework 0

作业0的内容主要是进行接下来的作业项目的环境配置。原本给的是一个已经配好环境的Ubuntu的虚拟机，装上就可以使用。本人试着用那个环境写了前面几个作业，确实是挺好用的，省去了配置环境的麻烦。但奈何本人不太习惯使用Linux系统（菜），故还是尝试在Win10 + Visual Studio下配置环境，完成接下来的作业。

配置的过程中参考了一些文章，贴在下面。

由于课程中的要求，后面的作业只会分析实现的思路，不会给出源代码。

如有不对的地方，欢迎指正。

## 外部依赖库的配置

Games101作业使用的框架为`eigen3`和`opencv`。在Visual Studio中配置外部依赖库非常麻烦，这里使用了`vcpkg`来简化流程。

### 1.安装vcpkg

可以直接使用git clone命令克隆一个当前版本。

```
git clone https://github.com/microsoft/vcpkg
//进行编译
.\vcpkg\bootstrap-vcpkg.bat
```

编译好以后会在同级目录下生成`vcpkg.exe`文件。编译期间，脚本会自动下载`vswhere`组件。

（不了解Git的同学可以进入上面命令的网址中下载zip包，在解压出来的目录中找到bootstrap-vcpkg.bat文件，双击运行）

### 2.安装（下载和编译）开源库

利用`vcpkg`进行安装。

```
./vcpkg/vcpkg.exe install eigen3:x64-windows
./vcpkg/vcpkg.exe install opencv:x64-windows
```

### 3.集成开源库

安装完开源库后，常规情况下，我们需要设置`include`目录、`lib`目录等，会有很多工作量。`vcpkg`提供了一套机制，可以全自动的适配目录，而开发者不需要关心已安装的库的目录在哪里，也不需要设置。这是`vcpkg`的一大优势。下面的命令将`vcpkg`安装的开源库集成到全局，“集成到全局”适用于Visual Studio开发环境和`msbuild`命令行。

```
./vcpkg/vcpkg.exe integrate install
```

当出现`Applied user-wide integration for this vcpkg root.`字样的时候，说明已经集成成功。这时候可以在任意的工程中使用安装好的第三方库。

## Visual Studio 中的配置

* 新建一个C++项目。
* 在项目-属性-配置属性-C/C++-语言-C++语言标准 中，选择C++17。据说是后面有使用到`std::optional`这个C++17特性。同时要使用x64平台。（项目中必须有C/C++代码才会出现C/C++这一栏）

![修改语言标准](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw0_c++17.png?raw=true "修改语言标准")

* 在项目-属性-配置属性-C/C++-预处理器-预处理器定义 中，加入`_CRT_SECURE_NO_WARNINGS`，消除某些警告。

![加入预处理器定义](https://github.com/Orznijiang/MyImageBed/blob/main/My-Learn/Games%20101/homework/homework_notes/hw0_define.png?raw=true "加入预处理器定义")

至此，就算是配置完成了。

## 参考链接

* https://zhuanlan.zhihu.com/p/360640432
* https://blog.csdn.net/cjmqas/article/details/79282847
* https://blog.csdn.net/cjmqas/article/details/79282847