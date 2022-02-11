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

1. **为什么C++有多种整型？**

   可以根据特定的需求选择最适合的类型。例如，用short存储空格，用long确保存储容量。

2. **声明与下述描述相符的变量**

   1. **short整数，值为80**

      `short num = 80;`

   2. **unsigned int整数，值为42110**

      `unsigned int num = 42110;`

   3. **值为3000000000的整数**

      `unsigned long num = 300000000;`

3. **C++提供了什么措施来防止超出整型的范围？**

   C++没有提供自动防止超出整形限制的功能，可以使用头文件climits来确定限制情况。

4. **33L与33之间有什么区别？**

   常量33L的类型为long，常亮33的类型为int。

5. **下面两条C++语句是否等价？**

   1. `char grade = 65；`

   2. `char grade = 'A'; `

      不真正等价，对某些系统来说是等价的。只有在使用ASCLL码的系统上，才将65设置为符号A。

6. **如何使用C++来找出编码88表示的字符？指出至少两种方法。**

   1. ```
      char c = 88;
      cout << c << endl;
      ```

   2. `cout.put(char(88));`

   3. `cout<<char(88)<<endl;`

   4. `cout<<(char)88<<endl;`

7. **将long值赋给float变量会导致舍入误差，将long值赋给double变量呢？将long long值赋给double变量呢？**

   double提供了至少13位的有效数字，若long的大小为4个字节（32位），则最大能到10位数，没有超出13位。而long long类型可以提供19位的有效数字，超过了13位，会导致舍入误差。

8. **下列C++表达式的结果分别是多少？**

   1. **8 * 9 + 2**

      74

   2. **6 * 3 / 4**

      4

   3. **3 / 4 * 6**

      0

   4. **6.0 * 3 / 4**

      4.5

   5. **15 % 4**

      3

9. **假设x1和x2是两个double变量，您要将它们作为整数相加，再将结果赋给一个整型变量。请编写一条完成这项任务的C++语句。如果要将它们作为double值相加并转换为int呢？**

   ```c++
   int num = （int）x1 + （int）x2；
   int num = int（x1 + x2）；

10. **下面每条语句声明的变量都是什么类型？**

    1. **auto cars = 15;**

       int

    2. **auto iou = 150.37;**

       float

    3. **auto level = 'B';**

       char

    4. **auto crat = U'/00002155';**

       char32_t

    5. **auto fract = 8.25f/255;**

       **double**



## 第4章 复合类型



