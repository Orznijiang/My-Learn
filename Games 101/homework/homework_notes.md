# Games101 作业环境配置与思路理解

## Homework 0

作业0的内容主要是进行接下来的作业项目的环境配置。原本给的是一个已经配好环境的Ubuntu的虚拟机，装上就可以使用。我试着用那个环境写了前面几个作业，确实是挺好用的，省去了配置环境的麻烦。但奈何本人不太习惯使用Linux系统（菜），故还是尝试在Win10 + Visual Studio下配置环境，完成作业。

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

### 参考链接

* https://zhuanlan.zhihu.com/p/360640432
* https://blog.csdn.net/cjmqas/article/details/79282847
* https://blog.csdn.net/cjmqas/article/details/79282847