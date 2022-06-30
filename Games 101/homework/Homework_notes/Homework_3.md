# Homework 3

作业3

## 前期准备

* 首先，将之前作业中的观察矩阵和投影矩阵的实现复制到`main.cpp`对应的函数中
* 根据`models`文件夹放置的具体位置，修改`main`函数中的`obj_path`路径
* 同样，根据实际情况修改`LoadFile()`函数中的路径，读取模型文件错误时会在窗口输出错误信息



## 





auto getInterpolateResult = [&](auto& propA, auto& propB, auto& propC) -> auto {
                    return Z * (alpha * propA / v[0].w() + beta * propB / v[1].w() + gamma * propC / v[2].w());
                };

在c++20以前，不可以用Lambda 表达式捕获结构化绑定。