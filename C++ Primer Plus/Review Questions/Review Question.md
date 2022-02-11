# 复习题

## 第2章 开始学习C++

1. **C++程序的模块叫什么？**

   函数

2. **预处理器编译指令：`#include <iostream>`是做什么用的？**

   在最终的编译之前，使用iostream文件的内容替换该编译指令

3. **语句：`using namespace std; `是做什么用的？**

   使得程序可以使用std名称空间中的定义

4. **如何打印短语“Hello World”然后开始新的一行？**

   `cout << "Hello World" <<endl;`

5. **如何创建名为cheeses的整数变量？**

   `Int cheeses;`

6. **如何将值32赋给变量cheeses？**

   `Cheeses = 32;`

7. **如何将键盘输入的值读入变量cheeses？**

   `cin >> cheeses;`

8. **如何打印“We have X varieties of cheeses." 其中X为变量cheeses的当前值？**

   `cout << "We have " << cheeses<< "varieties of cheeses." << endl;`

9. **以下函数原型指出了关于函数的哪些信息？**

   		int froop(double t);
   	调用froop函数时，应该提供一个double类型的参数，函数返回一个int值
   	void rattle(int n);
   	调用函数rattle时，应该提供一个int类型的参数。函数没有返回值
   	int prune(void);
   	调用函数prune时，不需要提供任何参数，函数返回一个int值

10. **定义函数时，什么情况下不必使用使用关键字return？**

    当函数不需要返回值时

11. **假设main()函数中包括如下代码：**

     `cout << "Please enter your PIN: ";`

     **而编译器指出cout是一个未知标识符。导致这种问题的原因很可能是什么？指出3种修复这种问题的方法。**

     	导致这种问题的原因很可能是没有使用对应的命名空间std，修复方法如下：
     	std::cout << "Please enter your PIN: ";
     	
     	using std::cout;
     	cout << "Please enter your PIN: ";
     	
     	using namespace std;
     	cout << "Please enter your PIN: ";



## 第3章 处理数据



