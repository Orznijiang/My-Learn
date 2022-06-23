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

1. **如何声明下述数据？**

   1. **actor是由30个char组成的数组**

      `char actor[30];`

   2. **betsie是由100个short组成的数组**

      `short betsie[100];`

   3. **chuck是由13个float组成的数组**

      `float chuck[13];`

   4. **dipsea是由64个long double组成的数组**

      `long double dipsea[64];`

2. **使用模板类array而不是数组来完成问题1。**

   1. `array<char, 30> actor;`
   2. `array<short, 100> betsie;`
   3. `array<float, 13> chuck;`
   4. `array<long double, 64> dipsea;`

3. **声明一个包含5个元素的int数组，并将它初始化为前5个正奇数。**

   `int num[5] = {1, 3, 5, 7, 9};`

4. **编写一条语句，将问题3中数组第一个元素和最后一个元素的和赋给变量even。**

   `int even = num[0] + num[4];`

5. **编写一条语句，显示float数组ideas中的第2个元素的值。**

   `cout << idea[1] << endl;`

6. **声明一个char的数组，并将其初始化为字符串“cheeseburger”。**

   `char lunch[] = "cheeseburger";`

7. **声明一个string对象，并将其初始化为字符串“Waldorf Salad”。**

   `std::string lunch = "Waldorf Salad";` 

8. **设计一个描述鱼的结构声明。结构中应当包括品种、重量（整数，单位为盎司）和长度（英寸，包括小数）。**

   ```
   struct fish{
   	char type[20];
   	int weight;
   	float length;
   };

9. **声明一个问题8中定义的结构的变量，并对它进行初始化。**

   `fish petes = {"trout", 12, 26.25};`

10. **用enum定义一个名为Response的类型，它包含Yes、No和Maybe等枚举量，其中Yes的值为1，No为0，Maybe为2。**

    `enum Response{Yes = 1, No = 0, Maybe = 2};`

    `enum Respomse{No, Yes, Maybe};`

11. **假设ted是一个double变量，请声明一个指向ted的指针，并使用该指针来显示ted的值。**

    ```
    double* p = &ted;
    cout << *p << endl;

12. **假设treacle是一个包含10个元素的float数组，请声明一个指向treacle的第一个元素的指针，并使用该指针来显示数组的第一个元素和最后一个元素。**

    ```
    float* p = treacle;
    cout << p[0] << p[9] << endl;

13. **编写一段代码，要求用户输入一个正整数，然后创建一个动态的int数组，其中包含的元素数目等于用户输入的值。首先使用new来完成这项任务，再使用vector对象来完成这项任务。**

    ```
    int size;
    cin >> size;
    int* p = new int[size];
    // std::vector<int> nums(size);

14. **下面的代码是否有效？如果有效，它将打印出什么结果？**

    `cout << （int*）“Home of the jolly bytes”；`

    有效。`“Home of the jolly bytes”`是一个字符串常量，将解释为字符串开始的地址，类型转换（int*）将地址强制转换为int指针，使其作为地址被打印，而不是打印字符串。只要int类型足够宽，能够存储该地址。

15. **编写一段代码，给问题8中描述的结构动态分配内存，再读取该结构的成员的值。**

    ```
    fish* pole = new fish;
    fish.weight = 3;

16. **程序清单4.6指出了混合输入数字和一行字符串时存储的问题。如果将下面的代码：**

    `cin.getline（address，80）；`

    **替换为**

    `cin >> address;`

    **将对程序的运行带来什么影响？**

    cin >> address使得程序跳过空白，直到找到非空白字符为止。然后它将读取字符，直到再次遇到空白为止。因此，它将跳过数字输入后的换行符，从而避免这种问题。另一方面，它只读取一个单词。

17. **声明一个vector对象和一个array对象，他们都包含10个string对象。指出所需的头文件，但不要使用using。使用const来指定要包含的string对象数。**

    ```
    #include <vector>
    #include <array>
    const int strNum = 10;
    
    std::vector<std::string> vecStr(strNum);
    std::array<std::string, strNum> arrStr;



### 编程练习注意点

* 对于char[]，`cin.get(name, size);`或者`cin.getline(name, size)`，区别是前者读取完一行保留换行符，后者读取换行符并替换为空字符`/0`。
* 对于string，由于是C++后面加入的实现，实现方式为友元函数，如`getline(cin, name);`
* 在读取行前读取数字会产生问题，读取数字会将换行符留在输入队列中，导致读取行刚开始就读取到换行符。解决方法是读取数字后使无参数的`cin.get();`读取换行符，再读取行。

### 笔记

* vector内部使用new和delete管理内存，存储在自由存储区或堆中。功能比数组强大，代价是效率稍低。
* array定长，存储在栈中（静态内存分配）。



## 第5章 循环和关系表达式

1. **入口条件循环和出口条件循环之间的区别是什么？各种C++循环分别属于其中哪一种？**

   入口条件循环在进入循环体之前将评估测试表达式。若表达式为false，则不会执行循环体。出口条件循环在处理循环体之后评估测试表达式，也就是说，无论表达式的结果如何，循环体至少执行一次。for和while是入口条件循环，do while是出口条件循环。

2. **如果下面的代码片段是有效程序的组成部分，它将打印什么内容？**

   ```
   int i;
   for(i = 0; i < 5; i++)
   	cout << i;
   	cout << endl;
   ```

   01234

3. **如果下面的代码片段是有效程序的组成部分，它将打印什么内容？**

   ```
   int j;
   for(j = 0; j < 11; j+=3)
   	cout << j;
   	cout << endl << j << endl;
   ```

   0369

   12

4. **如果下面的代码片段是有效程序的组成部分，它将打印什么内容？**

   ```
   int j = 5;
   while(++j < 9)
   	cout << j++ << endl;
   ```

   6

   8

5. **如果下面的代码片段是有效程序的组成部分，它将打印什么内容？**

   ```
   int k = 8;
   do
   	cout << " k = " << k << endl;
   while(k++ < 5);
   ```

   k = 8

6. **编写一个打印1、2、4、6、8、16、32、64的for循环，每轮循环都将计数变量的值乘以2。**

   ```
   for(int i = 1; i <= 64; i *= 2)
   	cout << i << " ";

7. **如何在循环体中包括多条语句？**

   将多个语句放在一个大括号中，形成一个代码块。

8. **下面的语句是否有效？如果无效，原因是什么？如果有效，它将完成什么工作？**

   1. ```
      int x = {1,024}；
      ```
      
      有效，**逗号取右值**，0开头为8进制数，转换为10进制为20，将20赋值给x。
      
   2. ```
      int y；
      y = 1,024；
      ```
      
      由于逗号的运算优先级是最低的，因此，先计算赋值运算，将1赋值给y。而整个表达式的值为右值，即10进制的20

9. **在查看输入方面，cin>>ch同cin.get(ch)和ch = cin.get()有什么不同？**

   第一种将跳过空格、换行符和制表符，后面两种可以读取这些字符。

### 编程练习注意点

* 函数`strcmp(str1, str2)`比较两个字符串，相等返回0，否则范围ASCLL码的差值



## 第6章 分支语句和逻辑运算符

1. **请看下面两个计算空格和换行符数目的代码片段：**

   ```
   // Version 1
   while(cin.get(ch)) // quit on eof
   {
   	if(ch == ' ')
   		spaces++;
   	if(ch == '\n')
   		newlines++;
   }
   
   // Version 2
   while(cin.get(ch)) // quit on eof
   {
   	if(ch == ' ')
   		spaces++;
   	else if(ch == '\n')
   		newlines++;
   }
   ```

   **第二种格式比第一种格式好在哪里呢？**

   这两个版本将给出相同的答案，但 `if else` 版本的效率更高。例如，考虑当`ch`为空格时的情况。版本1对空格加1，然后看他是否为换行符，这将浪费时间。

2. **在程序清单6.2中，用`ch+1`替换`++ch`将发生什么情况呢？**

   `++ch`和`ch+1`得到的数值相同。但`++ch`的类型为`char`，将作为字符打印，而`ch+1`是`int`类型（因为将`char`和`int`相加），将作为数字打印。

3. **请认真考虑下面的程序：**

   ```
   #include <iostream>
   using namespace std;
   int main()
   {
   	char ch;
   	int ct1, ct2;
   	
   	ct1 = ct2 = 0;
   	while((ch = cin.get()) != '$')
   	{
   		cout << ch;
   		ct1++;
   		if(ch = '$')
   			ct2++;
   		cout << ch;
   	}
   	cout << "ct1 = " << ct1 << ", ct2 = " << ct2 << "\n";
   	return 0;
   }
   ```

   **假设输入如下（请在每行末尾按回车键）：**

   ```
   Hi!
   Send $10 or $20 now!
   ```

   **则输出将是什么（还记得吗，输入被缓冲）？**

   注意`if`中是赋值语句。

   ```
   Hi!
   H$i$!$
   $Send $10 or $20 now!
   S$e$n$d$ $ct1 = 9, ct2 = 9
   ```

   因为赋值语句的值为左值，这里恒为`true`，因此每次循环`ct1`和`ct2`都增加1。同时，由于换行符也会被读取和打印，所以在第二行换行后的第三行先打印了`$`。

4. **创建表示下述条件的逻辑表达式**

   1. **`weight`大于或等于115，但小于125。**

      `weight >= 115 && weight < 125`

   2. **`ch`为q或Q。**

      `ch == 'q' || ch == 'Q'`

   3. **`x`为偶数，但不是26。**

      `x % 2 == 0 && x != 26` 

   4. **`x`为偶数，但不是26的倍数。**

      `x % 2 == 0 && x % 26 != 0`

   5. **`donation`为1000-2000或`guest`为1。**

      `donation >= 1000 && donation <= 2000 || guest == 1`

   6. **`ch`是小写字母或大写字母（假设小写字母是依次编码的，大写字母也是依次编码的，但在大小写字母间编码不是连续的）。**

      `(ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')`

5. **在英语中，“I will not not speak（我不会不说）”的意思与“I will speak（我要说）”相同。在C++中，`!!x`是否与`x`相同呢？**

   不一定。例如，若`x`为10，则`!x`为0，`!!x`为1。然而，如果`x`为`bool`变量，则`!!x`为`x`。

6. **创建一个条件表达式，其值为变量的绝对值。也就是说，如果变量`x`为正，则表达式的值为`x`；但如果`x`为负，则表达式的值为`-x`——这是一个正值。**

   `(x < 0)? -x : x;`

7. **用`switch`改写下面的代码片段：**

   ```
   if(ch == 'A')
   	a_grade++;
   else if(ch == 'B')
   	b_grade++;
   else if(ch == 'C')
   	c_grade++;
   else if(ch == 'D')
   	d_grade++;
   else
   	f_grade++;
   ```

   ```
   switch(ch)
   {
   	case 'A':
   		a_grade++;
   		break;
   	case 'B':
   		b_grade++;
   		break;
   	case 'C':
   		c_grade++;
   		break;
   	case 'D':
   		d_grade++;
   		break;
   	default:
   		f_grade++;
   		break;
   }

8. **对于程序清单6.10，与使用数字相比，使用字符（如a和c）表示菜单选项和case标签有何优点呢？（提示：想想用户输入q和输入5的情况）**

   如果使用整数标签，且用户输入了非整数（如q），则程序将因为整数输入不能处理字符而挂起。但是，如果使用字符标签，而用户输入了整数（如5），则字符输入将5作为字符处理。然后，`switch`语句的`default`部分将提示输入另一个字符。

9. **请看下面的代码片段：**

   ```
   int line = 0;
   char ch;
   while(cin.get(ch))
   {
   	if(ch == 'Q')
   		break;
   	if(ch != '\n')
   		continue;
   	iine++;
   }
   ```

   **请重写该代码片段，不要使用`break`和`continue`语句。**

   ```
   int line = 0;
   char ch;
   while(cin.get(ch) && ch != 'Q')
   {
   	if(ch == '\n')
   		line++;
   }

### 编程练习注意点

* `cctype`库中的各种与字符相关的函数
  * `isdigit()`：判断是否为数字字符
  * `isupper()`：判断是否为大写字母
  * `islower()`：判断是否为小写字母
  * `toupper()`：将小写字母转换为大写字母
  * `tolower()`：将大写字母转换为小写字母
* 对于命令行流（`iostream`）和文件流（`fstream`）
  * 对于字符使用`xx.get(char)`判断返回值较好
  * 对于其他类型一般使用`xx >> value`的返回值进行判断
  * 对于`fstream`
    * 使用`ofstream`对象可将数据输出到文件中（对应`cout`）
    * 使用`ifstream`对象可将数据从文件输入到变量中（对应`cin`）
    * 实际使用中发现，可以直接创建`fstream`对象，同时进行读写操作



## 第7章 函数——C++的编程模块

1. **使用函数的3个步骤是什么？**

   这3个步骤是定义函数、提供原型、调用函数。

2. **请创建与下面的函数匹配的函数原型。**

   1. **`igor()`没有参数，且没有返回值。**

      `void igor();`

   2. **`tofu()`接受一个`int`参数，并返回一个`float`。**

      `float tofu(int);`

   3. **`mpg()`接受两个`double`参数，并返回一个`double`。**

      `double mpg(double, double);`

   4. **`summation()`将`long`数组名和数组长度作为参数，并返回一个`long`值。**

      `long summation(long [], int);`

   5. **`doctor()`接受一个字符串参数（不能修改该字符串），并返回一个`double`值。**

      `double doctor(const char *);`

   6. **`ofcourse()`将`boss`结构作为参数，不返回值。**

      `void ofcourse(boss);`

   7. **`plot()`将`map`结构的指针作为参数，并返回一个字符串。**

      `char * plot(map *);`

3. **编写一个接受3个参数的函数：`int`数组名，数组长度和一个`int`值，并将数组中的所有元素都设置为该`int`值。**

   ```
   void set_array(int arr[], int size, int value)
   {
   	for(int i = 0;i < size; i++)
   		arr[i] = value;
   }

4. **编写一个接受3个参数的函数：指向数组区间中第一个元素的指针、指向数组区间中最后一个元素后面的指针以及一个`int`值，并将数组中的每个元素都设置为该`int`值。**

   ```
   void set_array(int * begin, int * end, int value)
   {
   	for(int * pt = begin;pt != end;pt++)
   		*pt = value;
   }

5. **编写将`double`数组名和数组长度作为参数，并返回该数组中最大值的函数。该函数不应修改数组的内容。**

   ```
   double biggest(const double foot[], int size)
   {
   	double max;
   	if(size < 1)
   	{
   		cout << "Invalid Array size of " << size << endl;
   		cout << "Returning a value of 0\n";
   		return 0;
   	}
   	else
   	{
   		max = foot[0];
   		for(int i = 1;i < size;i++)
   		{
   			if(foot[i] > max)
   				max = foot[i];
   		}
   		return max;
   	}
   }

6. **为什么不对类型为基本类型的函数参数使用`const`限定符？**

   将`const`限定符用于指针，以防止指向的原始数据被修改。程序传递基本类型（如`int`或`double`）时，它将按值传递，以便函数使用副本。这样，原始数据将得到保护。

7. **C++程序可使用哪3种C-风格字符串格式？**

   1. 存储在char数组中
   2. 用带双引号的字符串来表示
   3. 用指向字符串第一个字符的指针来表示

8. **编写一个函数，其原型如下：**

   ```
   int replace(char * str, char c1, char c2);
   ```

   **该函数将字符串中所有的`c1`都替换为`c2`，并返回替换次数。**

   ```
   int replace(char * str, char c1, char c2)
   {
   	int count = 0;
   	while(*str)
   	{
   		if(*str == c1)
   		{
   			*str = c2;
   			count++;
   		}
   		str++;
   	}
   	return count;
   }

9. **表达式`*"pizza"`的含义是什么？`"taco"[2]`呢？**

   * `*"pizza"`：C++将`"pizza"`解释为其第一个元素的地址，因此使用`*`运算符将得到第一个元素的值，即字符`p`。
   * `"taco"[2]`：C++将`"taco"`解释为其第一个元素的地址，因此它将`"taco"[2]`解释为第二个元素的值，即字符`c`。

   换句话来说，字符串常量的行为与数组名相同。

10. **C++允许按值传递结构，也允许传递结构的地址。如果`glitz`是一个结构变量，如何按值传递它？如何传递它的地址？这两种方法有何利弊？**

    * 按值传递：传递结构名`glitz`即可。
    * 传递地址：使用地址运算符`&glitz`。
    * 按值传递将自动保护原始数据，但这是以时间和内存为代价的。按地址传递可以节省时间和内存，但不能保护原始数据，除非对函数参数使用了`const`限定符。另外，按值传递意味着可以使用常规的结构成员表示法，但传递指针则必须使用间接成员运算符。

11. **函数`judge()`的返回类型为`int`，它将这样一个函数的地址作为参数：将`const char`指针作为参数，并返回一个`int`值。请编写`judge()`函数的原型。**

    ```
    int judge(int (*pf)(const char *));

12. **假设有如下结构声明：**

    ```
    struct applicant{
    	char name[30];
    	int credit_ratings[3];
    };
    ```

    1. **编写一个函数，它将`application`结构作为参数，并显示该结构的内容。**

       ```
       void display(applicant ap)
       {
       	cout << ap.name << endl;
       	for(int i = 0;i < 3;i++)
       	{
       		cout << ap.credit_ratings[i] << endl;
       	}
       }

    2. **编写一个函数，它将`application`结构的地址作为参数，并显示该参数指向的结构的内容。**

       ```
       void display(applicant * ap)
       {
       	cout << ap->name <<endl;
       	for(int i = 0;i < 3;i++)
       	{
       		cout << ap->credit_ratings[i] << endl;
       	}
       }

13. **假设函数`f1()`和`f2()`的原型如下：**

    ```
    void f1(applicant * a);
    const char * f2(const applicant * a1, const applicant * a2);
    ```

    **请将`p1`和`p2`分别声明为指向`f1`和`f2`的指针；将`ap`声明为一个数组，它包含5个类型与`p1`相同的指针；将`pa`声明为一个指针，它指向的数组包含10个类型与`p2`相同的指针。使用`typedef`来帮助完成这项工作。**

    ```
    typedef void(*p_f1)(applicant *);
    typedef const char * (p_f2)(const applicant *, const char *);
    p_f1 p1 = f1;
    p_f2 p2 = f2;
    p_f1 ap[5];
    p_f2 (*pa)[10];

### 编程练习注意点

* 下面的函数，当输入数字以外的字符时，会终止输入，返回一共输入的数字数量。且`if`中的`cin`始终会被运行到。

  ```
  int Fill_array(double* arr, int size) {
  	for (int i = 0; i < size; i++) {
  		cout << "number " << i << " : ";
  		if (!(cin >> arr[i])) {
  			cin.clear();
  			while (cin.get() != '\n') {
  				continue;
  			}
  			return i;
  		}
  	}
  	return size;
  ```

  * `clear()`函数清除`cin`发出的错误报告。
  * `while`循环清除输入缓冲中的所有输入，使得后面可以重新进行输入。



## 第8章 函数探幽

1. **哪种函数适合定义为内联函数？**

   只有一行代码的小型、非递归函数适合作为内联函数。

2. **假设`song()`函数的原型如下：**

   ```
   void song(const char * name, int times);
   ```

   1. **如何修改原型，使`times`的默认值为1？**

      `void song(const char * name, int times = 1);`

   2. **函数定义需要做哪些修改？**

      没有。只有原型包含默认值的信息。

   3. **能否为`name`提供默认值`"O. My Papa"`?**

      是的，如果保留`times`的默认值：

      ```
      void song(const char * name = "O. My Papa", int times = 1);

3. **编写`iquote()`的重载版本——显示其用双引号括起的参数。编写3个版本：一个用于`int`参数，一个用于`double`参数，一个用于`string`参数。**

   可以使用字符串`"\""`或字符`'"'`来打印引号，下面的函数演示了这两种方法。

   ```
   #include <iostream>
   #include <string>
   
   using namespace std;
   
   void iquote(int n)
   {
   	cout << "\"" << n << "\"" << endl;
   }
   
   void iquote(double x)
   {
   	cout << '"' << x << '"' << endl;
   }
   
   void iquote(string str)
   {
   	cout << "\"" << str << "\"" << endl;
   }

4. **下面是一个结构模板：**

   ```
   struct box
   {
   	char maker[40];
   	float height;
   	float width;
   	float length;
   	float volume;
   };
   ```

   1. **请编写一个函数，它将box结构的引用作为形参，并显示每个成员的值。**

      ```
      void show_box(const box & container)
      {
      	cout << "Made by " << container.maker << endl;
      	cout << "Height = " << container.height << endl;
      	cout << "Width = " << container.width << endl;
      	cout << "Volune = " << container.volume << endl;
      }

   2. **请编写一个函数，它将box结构的引用作为形参，并将volume成员设置为其他三边的乘积。**

      ```
      void set_box(box & crate)
      {
      	crate.volume = crate.height * crate.width * crate.length;
      }

5. **为让函数`fill()`和`show()`使用引用参数，需要对程序清单7.15做哪些修改？**

   首先，将原型修改成下面这样：

   ```
   // function to modify array object
   void fill(std::array<double, Seasons> & pa);
   // function that uses array object without modifying it
   void show(const std::array<double, Season> & da);
   ```

   注意，`show()`应使用`const`，以禁止修改对象。

   接下来，在`main()`中，将`fill()`调用改为下面这样：

   ```
   fill(expenses);
   ```

   函数`show()`的调用不需要修改。

   接下来，新的`fill()`应类似于下面这样：

   ```
   void fill(std::array<double, Season> & pa)
   {
   	using namespace std;
   	for(int i = 0;i < Season;i++){
   		cout << "Enter " << Snames[i] << " expenses: ";
   		cin >> pa[i]; // changed
   	}
   }
   ```

   注意到`(*pa)[i]`变成了更简单的`pa[i]`。

   最后，修改`show()`的函数头：

   ```
   void show(std::array<double, Season> & da)

6. **指出下面每个目标是否可以使用默认参数或函数重载完成，或者这两种方法都无法完成，并提供合适的原型。**

   1. **`mass(density, volume)`返回密度为`density`、体积为`volume`的物体的质量，而`mass(density)`返回密度为`density`体积为1.0立方米的物体的质量。这些值的类型都为`double`。**

      通过为第二个参数提供默认值：

      ```
      double mass(double density, double volume = 1.0);
      ```

      也可以通过函数重载：

      ```
      double mass(double density, double volume);
      double mass(double density);

   2. **`reapeat(10, "I'm OK")`将指定的字符串显示10次，而`reapeat("But you're kind of stupid")`将指定的字符串显示5次。**

      不能为重复的值使用默认值，因为必须从右到左提供默认值。可以使用重载：

      ```
      void repeat(int times, const char * str);
      void repeat(const char * str);
      ```

   3. **`average(3, 6)`返回两个`int`参数的平均值（`int`类型），而`average(3.0, 6.0)`返回两个`double`值的平均值（`double`类型）。**

      可以使用函数重载：

      ```
      int average(int a, int b);
      double average(double x, double y);

   4. **`mangle("I'm glad to meet you")`根据是将值赋给`char`变量还是`char *`变量，分别返回字符`l`和指向字符串`"I'm mad to gleet you"`的指针。**

      不能这样做，因为两个版本的特征标将相同。

7. **编写返回两个参数中较大值的函数模板。**

   ```
   templete <typename T>
   T max(T t1, T t2){
   	return t1 > t2 ? t1 : t2;
   }

8. **给定复习题7的模板和复习题4的`box`结构，提供一个模板具体化，它接受两个`box`参数，并返回体积较大的一个。**

   ```
   templete <> box max(box b1, box b2){
   	return b1.volume > b2.volume ? b1 : b2;
   }

9. **在下述代码（假定这些代码是一个完整程序的一部分）中，`v1`、`v2`、`v3`、`v4`和`v5`分别是哪种类型？**

   ```
   int g(int x);
   ...
   float m = 5.5f;
   float & rm = m;
   decltype(m) v1 = m;
   decltype(rm) v2 = m;
   decltype((m)) v3 = m;
   decltype(g(100)) v4;
   decltype(2.0 * m) v5;
   ```

   * `v1 : float`
   * `v2 : float &`
   * `v3 : float &`
   * `v4 : int`
   * `v5 : double`



### 编程练习注意点

* 字符串常量不能直接给char数组赋值
  * 可以使用`<cstring>`库中的`strcpy`函数
  * 或者用`<string>`库中的`string`类来代替
* `strlen`函数计算的字符串长度不包括`'\0'`
* `char`指针的数组，可以用两种方式表达
  * `char* p[]`
  * `char** p`

* 模板具体化和模板实例化不需要重新声明函数原型
* 具体化需要额外加一对`<>`



## 第9章 内存模型和名称空间

1. **对于下面的情况，应使用哪种存储方案？**

   1. **`homer`是函数的形参。**

      `homer`将自动成为自动变量。

   2. **`secret`变量由两个文件共享。**

      应该在一个文件中将`secret`定义为外部变量，并在第二个文件中使用`extern`来声明它。

   3. **`topsecret`变量由一个文件中的所有函数共享，但对于其他文件来说是隐藏的。**

      可以在外部定义前加上关键字`static`，将`topsecret`定义为一个有内部链接的静态变量。也可以在一个未命名的名称空间中进行定义。

   4. **`benncalled`记录包含它的函数被调用的次数。**

      应在函数的声明前加上关键字`static`，将`beencalled`定义为一个本地静态变量。

2. **`using`声明和`using`编译指令之间有何区别？**

   `using`声明使得名称空间中的单个名称可用，其作用域与`using`所在的声明区域相同。`using`编译指令使名称空间中的所有名称可用。使用`using`编译指令时，就像在一个包含`using`声明和名称空间本身的最小声明区域中声明了这些名称一样。

3. **重新编写下面的代码，使其不使用`using`声明和`using`编译指令。**

   ```
   #include <iostream>
   using namespace std;
   int main()
   {
   	double x;
   	cout << "Enter value: ";
   	while(! (cin >> x))
   	{
   		cout << "Bad input. Please enter a number: ";
   		cin.clear();
   		while(cin.get() != '\n')
   			continue;
   	}
   	cout << "Value = " << x << endl;
   	return 0;
   }
   ```

   ```
   #include <iostream>
   int main()
   {
   	double x;
   	std::cout << "Enter value: ";
   	while(! (std::cin >> x))
   	{
   		std::cout << "Bad input. Please enter a number: ";
   		std::cin.clear();
   		while(std::cin.get() != '\n')
   			continue;
   	}
   	std::cout << "Value = " << x << std::endl;
   	return 0;
   }

4. **重新编写下面的代码，使其使用`using`声明，而不是`using`编译指令。**

   ```
   #include <iostream>
   using namespace std;
   int main()
   {
   	double x;
   	cout << "Enter value: ";
   	while(! (cin >> x))
   	{
   		cout << "Bad input. Please enter a number: ";
   		cin.clear();
   		while(cin.get() != '\n')
   			continue;
   	}
   	cout << "Value = " << x << endl;
   	return 0;
   }
   ```

   ```
   #include <iostream>
   int main()
   {
   	using std::cin;
   	using std::cout;
   	using std::endl;
   	double x;
   	cout << "Enter value: ";
   	while(! (cin >> x))
   	{
   		cout << "Bad input. Please enter a number: ";
   		cin.clear();
   		while(cin.get() != '\n')
   			continue;
   	}
   	cout << "Value = " << x << endl;
   	return 0;
   }

5. **在一个文件中调用`average(3,6)`函数时，它返回两个`int`参数的`int`平均值，在同一个程序的另一个文件中调用时，它返回两个`int`参数的`double`平均值。应如何实现？**

   可以在每个文件中包含单独的静态函数定义。或者每个文件都在未命名的名称空间中定义一个合适的`average()`函数。

6. **下面的程序由两个文件组成，该程序显示什么内容？**

   ```
   // file1.cpp
   #include <iostream>
   using namespace std;
   void other();
   void another();
   int x = 10;
   int y;
   
   int main()
   {
   	cout << x << endl;
   	{
   		int x = 4;
   		cout << x << endl;
   		cout << y << endl;
   	}
   	other();
   	another();
   	return 0;
   }
   
   void other()
   {
   	int y = 1;
   	cout << "Other: " << x << ", " << y << endl;
   }
   
   // file2.cpp
   #include <iostream>
   using namespace std;
   extern int x;
   namespace
   {
   	int y = -4;
   }
   
   void another()
   {
   	cout << "another(): " << x << ", " << y << endl;
   }
   ```

   ```
   10
   4
   0
   Other: 10, 1
   another: 10, -4

7. **下面的代码将显示什么内容？**

   ```
   #include <iostream>
   using namespace std;
   void other();
   namespace n1
   {
   	int x = 1;
   }
   
   namespace n2
   {
   	int x = 2;
   }
   
   int main()
   {
   	using namespace n1;
   	cout << x << endl;
   	{
   		int x = 4;
   		cout << x << ", " << n1::x << ", " << n2::x << endl;
   	}
   	using n2::x;
   	cout << x << endl;
   	other();
   	return 0;
   }
   
   void other()
   {
   	using namespace n2;
   	cout << x << endl;
   	{
   		int x = 4;
   		cout << x << ", " << n1::x << ", " << n2::x << endl;
   	}
   	using n2::x;
   	cout << x << endl;
   }
   ```

   ```
   1
   4, 1, 2
   2
   2
   4, 1, 2
   2

### 编程练习注意点

* 定位`new`使用的缓冲位置的数据类型不需要和要放入的数据类型一致



## 第10章 对象和类

1. **什么是类？**

   类是用户定义的类型的定义。类声明指定了数据将如何存储，同时指定了用来访问和操纵这些数据的方法（类成员函数）。

2. **类如何实现抽象、封装和数据隐藏？**

   类成员函数表示人们可以使用类方法的公有接口对类对象执行的操作，这是抽象。类的数据成员可以是私有的（默认值），这意味着只能通过成员函数来访问这些数据，这是数据隐藏。实现的具体细节（如数据表示和方法的代码）都是隐藏的，这是封装。

3. **对象和类之间的关系是什么？**

   类定义了一种类型，包括如何使用它。对象是一个变量或其他数据对象（如由`new`生成的），并根据类定义被创建和使用。类和对象之间的关系同标准类型与其变量之间的关系相同。

4. **除了是函数之外，类函数成员与类数据成员之间的区别是什么？**

   如果创建给定类的多个对象，则每个对象都有其自己的数据内存空间；但所有的对象都使用同一组成员函数（通常，方法是公有的，而数据是私有的，但这只是策略方面的问题，而不是对类的要求）。

5. **定义一个类来表示银行账户。数据成员包括储户姓名、账号（使用字符串）和存款。成员函数执行如下操作：**

   1. **创建一个对象并将其初始化；**
   2. **显示储户姓名、账号和存款；**
   3. **存入参数指定的存款；**
   4. **取出参数指定的存款；**

   **请提供类声明，而不用给出方法实现。（编程练习1将要求编写实现）**

   ```
   #include <string>
   // class definition
   class BankAccount
   {
   	private:
   		std::string name;
   		std::string acctnum;
   		double balance;
   	public:
   		BankAccount(const std::string& client, const std::string& num, double bal = 0.0);
   		void show(void) const;
   		void deposit(double cash);
   		void withdraw(double cash);
   };

6. **类构造函数在何时被调用？类析构函数呢？**

   在创建类对象或显示调用构造函数时，类的构造函数都将被调用。当对象过期时，类的析构函数将被调用。

7. **给出复习题5中的银行账户类的构造函数的代码。**

   ```
   BankAccount::BankAccount(const std::string& client, const std::string& num, double bal)
   {
   	name = client;
   	acctnum = num;
   	balance = bal;
   }
   ```

   请记住，默认参数位于原型中，而不是函数定义中。

8. **什么是默认构造函数，拥有默认构造函数有何好处？**

   默认构造函数是没有参数或所有参数都有默认值的构造函数。拥有默认构造函数后，可以声明对象，而不初始化它，即使已经定义了初始化构造函数。它还使得能够声明数组。

9. **修改`Stock`类的定义（`stock20.h`中的版本），使之包含返回各个数据成员值的成员函数。注意：返回公司名的成员函数不应为修改数组提供便利，也就是说，不能简单地返回`string`引用。**

   ```
   // stock30.h
   #ifndef STOCK30_H_
   #define STOCK30_H_
   #include <string>
   
   class Stock
   {
   	private:
   		std::string company;
   		long shares;
   		double share_val;
   		double total_val;
   		void set_tot() { total_val = shares * share_val; }
   	public:
   		Stock(); // default constructor
   		Stock(const std::string& co, long n, double pr);
   		~Stock() {} // do-nothing destructor
   		void buy(long num, double price);
   		void sell(long num, double price);
   		void update(double price);
   		void show() const;
   		const Stock& topval(const Stock& s) const;
   		int numshares() const { return shares; }
   		double shareval() const { return share_val; }
   		double totalval() const { return total_val; }
   		const string& co_name() const { return company; }
   };
   
   #endif

10. **`this`和`*this`是什么？**

    `this`指针是类方法可以使用的指针，它指向用于调用方法的对象。因此，`this`是对象的地址，`*this`是对象本身。

### 编程练习注意点

* 在类的公有函数中调用构造函数进行初始化：
  * `*this = constructor();`
* `typedef int hahaha;`:代码中的`hahaha`与`int`等同（`hahaha`为别名）
* 函数指针作为函数参数时，调用该函数时的函数实参可以加取地址符`&`，也可以不加

### 笔记

* 定义作用域为类的常量（下面的定义都在类中）
  * `const int num = 1;`不行，因为这种创建在具体的对象创建前没有值
  * 枚举`enum{num = 1};`可以。用这种方法声明的枚举不会创建类数据成员，而是编译器在遇到`num`时会用具体的数字来代替
  * `static const int num = 1;`可以。该常量将与其他静态变量存储在一起，而不是在对象中，但作用域为这个类。

* 作用域内枚举
  * `enum egg{small};`会和另一个枚举变量`enum apple{small};`中的枚举值`small`发生冲突，因为它们在同一个作用域内。同时它们可以进行隐式的转换。
  * `enum class egg{small};`则不会产生冲突，因为必须使用枚举名进行限定才能取到枚举量：`egg::small`。这里`class`也可用`struct`代替。但它们必须进行显式转换。



## 第11章 使用类

1. **使用成员函数为`Stonewt`类重载乘法运算符，该运算符将数据成员与`double`类型的值相乘。注意，用英石和磅表示时，需要进位。也就是说，将10英石8磅乘以2等于21英石2磅。**

   ```
   // prototype
   Stonewt opetator*(double mult);
   
   // definition - let constructor do the work
   Stonewt Stonewt::operator*(double mult){
   	return Stonewt(mult * pounds);
   }

2. **友元函数与成员函数之间的区别是什么？**

   成员函数是类定义的一部分，通过特定的对象来调用。成员函数可以隐式访问调用对象。友元函数不是类的组成部分，因此被称为直接函数调用。友元函数不能隐式访问类对象，而必须必须将对象用于作为参数传递的对象。

3. **非成员函数必须是友元才能访问类成员吗？**

   要访问类的私有成员，则必须使用友元函数；只需要访问类的公有成员时，不需要友元函数。

4. **使用友元函数为`Stonewt`类重载乘法运算符，该运算符将`double`值与`Stonewt`值相乘。**

   ```
   // prototype
   friend Stonewt operator*(double mult, const Stonewt& s);
   
   // definition - let constructor do the work
   Stonewt operator*(double mult, const Stonewt& s){
   	return Stonewt(mult * s.pounds);
   }

5. **哪些运算符不能重载？**

   * `sizeof`
   * `.`
   * `.*`
   * `::`
   * `?:`

6. **在重载运算符`=、()、[]、->`时，有什么限制？**

   这些运算符必须使用成员函数来定义。

7. **为`Vector`类定义一个转换函数，将`Vector`类转换为一个`double`类型的值，后者表示矢量的长度。**

   ```
   // prototype and inline definition
   operator double() { return mag; }
   ```

   但使用普通的`magval()`方法比定义该转换函数更符合逻辑。



### 	编程练习注意点

* 在比较数字时，注意变量的类型。例如，将`unsigned long`变量的值与`int`变量的值进行比较，不一定能得到正确的结果
* 不能使用`using`指令将类范围中的名称带入命名空间范围。只能`using`在命名空间范围内，在不同的命名空间中定义的名称。



## 第12章 类和动态内存分配

1. **假设`String`类有如下私有成员：**

   ```
   class String
   {
   	private:
   		char* str; // points to string allocated by new
   		int len;   // holds length of string
   		// ...
   };
   ```

   1. **下述默认构造函数有什么问题？**

      ```
      String::String() {}
      ```

      语法是正确的，但该构造函数没有初始化`str`指针，应将其设置为`NULL`或使用`new []`来初始化。

   2. **下述构造函数有什么问题？**

      ```
      String::String(const char* s)
      {
      	str = s;
      	len = strlen(s);
      }
      ```

      该构造函数没有创建新的字符串，而只是复制了原有字符串的地址。应使用`new []`和`strcpy()`。

   3. **下述构造函数有什么问题？**

      ```
      String::String(const char* s)
      {
      	strcpy(str, s);
      	len = strlen(s);
      }
      ```

      该构造函数复制了字符串，但没有事先给它分配存储空间。应使用`new char[len + 1]`来分配适当数量的内存。

2. **如果你定义了一个类，其指针成员是使用`new`初始化的，请指出可能出现的3个问题以及如何纠正这些问题。**

   1. 首先，当这种类型的对象过期时，对象的成员指针指向的数据仍将保留在内存中，这将占用空间，同时不可访问，因为指针已经丢失。可以让类析构函数删除构造函数中`new`分配的内存，来解决这种问题。
   2. 其次，析构函数释放这种内存后，如果程序将这样的对象初始化为另一个对象，则析构函数将试图释放这些内存两次。这是因为将一个对象初始化为另一个对象的默认初始化，将复制指针值，但不复制指向的数据，这将使两个指针指向相同的数据。解决方法是，定义一个复制构造函数，使初始化复制指向的数据。
   3. 第三，将一个对象赋给另一个对象也将导致两个指针指向相同的数据。解决方法是重载赋值运算符，使之复制数据，而不是指针。

3. **如果没有显式提供类方法，编译器将自动生成哪些类方法？请描述这些隐式生成的函数的行为。**

   C++自动提供了下面这些成员函数：

   * 如果没有定义构造函数，将提供默认构造函数。
   * 如果没有定义复制构造函数，将提供复制构造函数。
   * 如果没有定义赋值运算符，将提供赋值运算符。
   * 如果没有定义析构函数，将提供默认析构函数。
   * 如果没有定义地址运算符，将提供地址运算符。

   默认构造函数不完成任何工作，但使得能够声明数组和未初始化的对象。默认复制构造函数和默认赋值运算符使用成员赋值。默认析构函数也不完成任何工作。隐式地址运算符返回调用对象的地址（即`this`指针的值）。

4. **找出并改正下述类声明中的错误：**

   ```
   class nifty
   {
   	// data
   	char personality[];
   	int talents;
   	// methods
   	nifty();
   	nifty(char* s);
   	ostream& operator<<(ostream& os, nifty& n);
   };
   
   nifty:nifty()
   {
   	personality = NULL;
   	talents = 0;
   }
   
   nifty:nifty(char* s)
   {
   	personality = new char [strlen(s)];
   	personality = s;
   	talents = 0;
   }
   
   ostream& nifty:operator<<(ostream& os, nifty& n)
   {
   	os << n;
   }
   ```

   应将`personality`成员声明为字符数组或`char`指针，且没有将方法设置为公有的。修改如下：

   ```
   class nifty
   {
   	// data
   	char personality[40]; // provide array size
   	int talents;
   public:                   // needed
   	// methods
   	nifty();
   	nifty(char* s);
   	friend ostream& operator<<(ostream& os, const nifty& n); // add friend, const
   };
   
   nifty:nifty()
   {
   	personality = '\0';
   	talents = 0;
   }
   
   nifty:nifty(char* s)
   {
   	//personality = new char [strlen(s)];
   	strcpy(personality, s);
   	talents = strlen(s);
   }
   
   ostream& nifty:operator<<(ostream& os, nifty& n)
   {
   	os << n.personality << '\n';
   	os << n.talents << '\n';
   	return os
   }

5. **对于下面的类声明：**

   ```
   class Golfer
   {
   	private:
   		char* fullname; // points to string containing golfer's name
   		int games;      // holds number of golf games played
   		int* scores;    // points to first element of array of golf scores
   	public:
   		Golfer();
   		Golfer(const char* name, int g = 0);
   		// creates empty dynamic array of g elements if g > 0
   		Golfer(const Golfer& g);
   		~Golfer();
   };
   ```

   1. **下列各条语句将调用哪些类方法？**

      ```
      Golfer nancy;                     // #1
      Golfer lulu("Littlw Lulu");       // #2
      Golfer roy("Roy Hobbs", 12);      // #3
      Golfer* par = new Golfer;         // #4
      Golfer next = lulu;               // #5
      Golfer hazzard = "Weed Thwacker"; // #6
      *par = nancy;                     // #7
      nancy = "Nancy Putter";           // #8
      ```

      1. `Golfer()`
      2. `Golfer(const char* name, int g = 0)`
      3. `Golfer(const char* name, int g = 0)`
      4. `Golfer()`
      5. `Golfer(const Golfer& g)` 或加上赋值运算符
      6. `Golfer(const char* name, int g = 0)` 或加上赋值运算符
      7. 赋值运算符
      8. `Golfer(const char* name, int g = 0)` 以及赋值运算符

   2. **很明显，类需要有另外几个方法才能更有用，但是类需要哪些方法才能防止数据被破坏呢？**

      类应定义一个复制数据（深拷贝，而不是地址）的赋值运算符。



### 笔记

* 不能在类声明中初始化静态成员变量（`static int num = 1;`），这是因为声明描述了如何分配内存，但并不分配内存
* 对于静态类成员，可以在类声明之外使用单独的语句来进行初始化，这是因为静态类成员是单独存储的，而不是对象的组成部分（初始化时是否需要带上static？）
* C++自动提供了下面这些成员函数：
  * 默认构造函数，如果没有定义构造函数
  * 默认析构函数，如果没有定义
  * 复制构造函数，如果没有定义
  * 赋值运算符，如果没有定义
  * 地址运算符，如果没有定义
* 初始化对象时，下面的方式并不一定会使用赋值运算符：`StringBad metoo = knot;`可能有两种情况：
  * 使用复制构造函数创建一个临时对象，然后通过赋值运算符将临时对象的值复制到新对象中
  * 直接使用复制构造函数创建并初始化`metoo`对象
* 赋值运算符是只能由类成员函数重载的运算符之一
* `delete[]`与使用`new[]`初始化的指针和空指针`int* p = 0;/int* p = nullptr;`都兼容，对于其他方式初始化的指针（包括未初始化的指针），结果不确定
* 表示空指针的方式
  * C++98
    * `0`
    * `(void*)0`
    * `NULL`：表示空指针的C语言宏
  * C++11
    * `nullptr`：关键字
* `delete`可与常规`new`运算符配合使用，但不能与定位`new`运算符配合使用。因此，需要显示地为使用定位`new`运算符创建的对象调用析构函数
* 技术总结：12.6节
* 对于非静态`const`类成员以及引用的类成员，必须使用初始化列表的方式进行初始化，其他类成员可选
* 数据成员被初始化的顺序与它们出现在类声明中的顺序相同，与初始化器中的排列顺序无关（大括号内的语句视为赋值）
* C++11允许直接在类声明中进行初始化，这与初始化列表等价。这时，构造函数的初始化列表以及括号内的语句可以覆盖声明中的初始化值



## 第13章 类继承

1. **派生类从基类那里继承了什么？**

   基类的公有成员为派生类的公有成员。基类的保护成员为派生类的保护成员。基类的私有成员被继承，但不能直接访问。

2. **派生类不能从基类那里继承什么？**

   不能继承构造函数、析构函数、赋值运算符。

3. **假设`baseDMA::operator=()`函数的返回类型为`void`，而不是`baseDMA &`，这将有什么后果？如果返回类型为`baseDMA`，而不是`baseDMA &`，又将有什么后果？**

   如果返回的类型为`void`，仍可以使用单个赋值，但不能使用连续赋值。

   如果返回的是一个对象，而不是引用，则方法的执行速度会变慢，因为返回语句需要复制对象。

4. **创建和删除派生类对象时，构造函数和析构函数调用的顺序是怎样的？**

   按派生的顺序调用构造函数，最早的构造函数最先调用。调用析构函数的顺序相反。

5. **如果派生类没有添加任何数据成员，它是否需要构造函数？**

   需要，每个类都必须有自己的构造函数。如果派生类没有添加新成员，则构造函数可以为空，但必须存在。

6. **如果基类和派生类定义了同名的方法，当派生类对象调用该方法时，被调用的将是哪个方法？**

   只调用派生类方法。它取代基类定义。仅当派生类没有重新定义方法或使用作用域解析运算符时，才会调用基类方法。然而，应将所有需要重新定义的函数声明为虚函数。

7. **在什么情况下，派生类应定义赋值运算符？**

   如果派生类构造函数使用`new`或`new[]`运算符来初始化类的指针成员，则应定义一个赋值运算符。更普遍地说，如果对于派生类成员来说，默认赋值不正确，则应定义赋值运算符。

8. **可以将派生类对象的地址赋给基类指针吗？可以将基类对象的地址赋给派生类指针吗？**

   可以将派生类对象的地址赋给基类指针。

   只有通过显式的类型转换，才可以将基类对象的地址赋给派生类指针（向下转换），而使用这样的指针不一定安全。

9. **可以将派生类对象赋给基类对象吗？可以将基类对象赋给派生类对象吗？**

   可以将派生类对象赋给基类对象。对于派生类中新增的数据成员都不会传递给基类对象。程序将使用基类的赋值运算符。

   仅当派生类定义了转换运算符（即包含将基类引用作为唯一参数的构造函数）或使用基类为参数的赋值运算符时，相反方向的赋值才是可能的。

10. **假设定义了一个函数，它将基类对象的引用作为参数。为什么该函数也可以将派生类对象作为参数？**

    因为C++允许基类引用指向从该基类派生而来的类型。

11. **假设定义了一个函数，它将基类对象作为参数（即函数按值传递基类对象）。为什么该函数也可以将派生类对象作为参数？**

    按值传递将调用复制构造函数。由于形参是基类对象，因此将调用基类的复制构造函数。复制构造函数以基类引用为参数，该引用可以指向作为参数传递的派生对象。最终结果是，将生成一个新的基类对象，其成员对应于派生对象的基类部分。

12. **为什么通常按引用传递对象比按值传递对象的效率更高？**

    按引用（而不是按值）传递对象，这样可以确保函数从虚函数受益。另外，按引用（而不是按值）传递对象可以节省内存和时间，尤其对于大型对象来说。按值传递对象的主要优点在于可以保护原始数据，但可以通过将引用作为`const`类型传递，来达到同样的目的。

13. **假设`Corporation`是基类，`PublicCorporation`是派生类。再假设这两个类都定义了`head()`函数，`ph`是指向`Corporation`类型的指针，且被赋给了一个`PublicCorporation`对象的地址。如果基类将`head()`定义为：**

    1. **常规非虚方法；**
    2. **虚方法；**

    **则`ph -> head()`将被如何解释？**

    如果是常规方法，则调用`Corporation::head()`；如果是一个虚方法，则调用`PublicCorporation::head()`。

14. **下述代码有什么问题？**

    ```
    class Kitchen
    {
    	private:
    		double kit_sq_ft;
    	public:
    		Kitchen() { kit_sq_ft = 0.0; }
    		virtual double area() const { return kit_sq_ft \* kit_sq_ft; }
    };
    
    class House : public Kitchen
    {
    	private:
    		double all_sq_ft;
    	public:
    		House() { all_sq_ft += kit_sq_ft; }
    		double area(const char* s) const { cout << s; return all_sq_ft; }
    };
    ```

    首先，这种情况不符合is-a模型，因此公有继承不适用。其次，`House`中的`area()`定义隐藏了同名方法的`Kitchen`版本，因为这两个方法的特征标不同。



### 笔记

* 在构造列表中对类成员进行赋值，是在实现对类成员进行默认初始化（若成员也是对象，则调用默认构造函数）后，使用赋值运算符进行赋值。若在初始化列表中进行赋值，则是直接进行初始化（若类成员是对象，则直接构造），少了一个赋值的操作
* 创建派生类对象时，程序首先创建基类对象
* 基类指针可以在不进行显式转换的情况下指向派生类对象；基类引用可以在不进行显式转换的情况下引用派生类对象
* 方法在基类中被声明为虚方法后，它在派生类中将自动成为虚方法，无论是否显式添加关键字`virtual`
* 在使用虚函数的例子中，为基类声明一个虚析构函数也是一种惯例（即使或许当前基类并不需要显式的析构函数）
* 关键字`virtual`只用于类声明中的方法原型中
* 在派生类方法中，标准技术是使用作用域解析运算符来调用基类方法。（名字唯一的方法实际上可以不用）
* 编译器对非虚方法使用静态联编，对虚方法使用动态联编
* **虚函数表原理：13.4.2.2**
* 友元不能是虚函数，因为友元不是类成员，而只有成员才能使虚函数（可以让友元函数调用虚成员函数来解决）
* 在派生类中重新定义基类继承的方法并不是重载，无论方法的参数列表是否相同，该操作将隐藏所有的同名基类方法
* 在函数原型中使用`=0`可以指出该类是一个抽象基类，在类中可以不定义该函数（也可以定义）
* **类设计回顾：13.8**
* 构造函数、析构函数、赋值运算符是不能被继承的
* 赋值运算符重载函数 参数可以是其他类型吗？



## 第14章 C++中的代码重用

1. **以A栏的类为基类时，B栏的类采用公有派生还是私有派生更合适。**

   ```
   A						B
   
   class Bear				class PolarBear
   class Kitchen			class Home
   class Person			class Programmer
   class Person			class HorseAndJockey
   class Person、class Automobile 	class Driver
   ```

   1. 公有
   2. 私有
   3. 公有
   4. 私有
   5. Person公有，Automobile私有

2. **假设有下面的定义：**

   ```
   class Frabjous
   {
   	private:
   		char fab[20];
   	public:
   		Frabjous(const char* s = "C++") : fabs(s) {  }
   		virtual void tell() { cout << fab; }
   };
   
   class Gloam
   {
   	private:
   		int glip;
   		Frabjous fb;
   	public:
   		Gloam(int g = 0, const char* s = "C++");
   		Gloam(int g, const Frabjous& f);
   		void tell();
   };
   ```

   **假设`Gloam`版本的`tell()`应显示`glip`和`fb`的值，请为这3个`Gloam`方法提供定义。**

   ```
   Gloam::Gloam(int g, const char* s) : glip(g), fb(s) {}
   Gloam::Gloam(int g, const Frabjous& fr) : glip(g), fb(fr) {}
   // note: the above uses the default Frabjous copy constructor
   void Gloam::tell()
   {
   	fb.tell();
   	cout << glip << endl;
   }

3. **假设有下面的定义：**

   ```
   class Frabjous
   {
   	private:
   		char fab[20];
   	public:
   		Frabjous(const char* s = "C++") : fabs(s) {  }
   		virtual void tell() { cout << fab; }
   };
   
   class Gloam : private Frabjous
   {
   	private:
   		int glip;
   	public:
   		Gloam(int g = 0, const char* s = "C++");
   		Gloam(int g, const Frabjous& f);
   		void tell();
   };
   ```

   **假设`Gloam`版本的`tell()`应显示`glip`和`fb`的值，请为这3个`Gloam`方法提供定义。**

   ```
   Gloam::Gloam(int g, const char* s) : glip(g), Frabjous(s) {}
   Gloam::Gloam(int g, const Frabjous& fr) : glip(g), Frabjous(fr) {}
   // note: the above uses the default Frabjous copy constructor
   void Gloam::tell()
   {
   	Frabjous::tell();
   	cout << glip >> endl;
   }

4. **假设有下面的定义，它是基于程序清单14.13中的`Stack`模板和程序清单14.10中的`Worker`类的：**

   ```
   Stack<Worker *> sw;
   ```

   **请写出将生成的类声明。只实现类声明，不实现非内联类方法。**

   ```
   templte <class Type>
   class Stack<Worker*>
   {
   	private:
   		enum{MAX = 10};		// constant specific to class
   		Worker * items[MAX];// holds stack items
   		int top;			// index for top stack item
   	public:
   		Stack();
   		bool isempty();
   		bool isfull();
   		bool push(const Worker * & item);	// add item to stack
   		bool pop(Worker * & item);			// pop top into item
   };

5. **使用本章中的模板定义对下面的内容进行定义：**

   * **`string`对象数组；**

     `ArrayTP<string> sa;`
     
   * **`double`数组栈；**

     `StackTP<ArrayTP<double>> stck_arr_db;`

   * **指向`Worker`对象的指针的栈数组；**

     `ArrayTP<SatckTP<Worker*>> arr_stk_wpr;`

   **程序清单14.18生成了多少个模板类定义？**

   程序清单14.18生成4个模板：

   * `ArrayTP<int, 10>`
   * `ArrayTP<double, 10>`
   * `ArrayTP<int, 5>`
   * `ArrayTP<ArrayTP<int, 5>, 10>`

6. **指出虚基类与非虚基类之间的区别。**

   如果两条继承路线有相同的祖先，则类中将包含祖先成员的两个拷贝。将祖先类作为虚基类可以解决这种问题。



### 笔记

* 在私有继承中，未进行显式类型转换的派生类引用或指针，无法赋给基类的引用或指针

* 通常，应使用包含来建立has-a关系；如果新类需要访问原有类的保护成员，或需要重新定义虚函数，则应使用私有继承

* 保护、私有继承下，使基类的方法在派生类外面可用

  * 用派生类的公有方法进行包装
  * 在派生类的公有部分使用`using`声明，指出派生类可以使用特定的基类成员（只适用于继承，不适用于包含）

* 除非显式写出，否则编译器认为继承是私有的

* C++在基类是虚的时，禁止信息通过中间类自动传给基类。因此，最终的派生类（存在间接的虚基类）需要显式地调用构造函数构造虚基类对象，否则使用默认构造函数

* 由于模板不是函数，它们不能单独编译。模板必须与特定的模板实例化请求一起使用。为此，最简单的方法是将所有模板信息放在一个头文件中，并在要使用这些模板的文件中包含该头文件

* 模板类使用时必须显式地提供所需的类型，这与常规的函数模板是不同的，因为编译器可以根据函数的参数类型来确定要生成哪种函数

* 表达式参数可以是整型、枚举、引用或指针，模板代码不能修改参数的值，也不能使用参数的地址。另外，实例化模板时，用作表达式参数的值必须是常量表达式

* 可以为类模板类型参数提供默认值，但不能为函数模板参数提供默认值。可以为非类型参数提供默认值，这对于类模板和函数模板都是适用的

* 编译器在需要对象之前不会生成类的隐式实例化（仅声明无效，如指向其的指针，必须进行要分配空间的操作）

* 模板的显式实例化必须位于模板定义所在的名称空间中

* 显式具体化（explicit specialization）是特定类型（用于替换模板中的泛型）的定义

* 模板的友元分3类：

  * 非模板友元
  * 约束模板友元
  * 非约束模板友元

* C++11可为模板提供别名

  ```
  template <typename T>
  	using arrtype = std::array<T, 12>;
  arraytype<int> days; // = std::array<int, 12>
  ```

  用于非模板时，这种用法与常规`typedef`等价

  ```
  typedef const char* pc1;
  using pc1 = const char*;





## 第15章 友元、异常和其他

1. **下面建立友元的尝试有什么错误？**

   1. ```
      class snap
      {
      	friend clasp;
      	...
      };
      class clasp {...};
      ```

      友元类声明缺少关键字`class`：`friend class clasp;`

   2. ```
      class cuff
      {
      	public:
      		void snip(muff &) {...}
      		...
      };
      
      class muff
      {
      	friend void cuff::snip(muff &);
      	...
      };
      ```

      需要一个前向声明，以便编译器能够解释`void snip(muff &)`：

      ```
      class muff; // forward declaration
      class cuff
      {
      	public:
      		void snip(muff &) {...}
      		...
      };
      
      class muff
      {
      	friend void cuff::snip(muff &);
      	...
      };

   3. ```
      class muff
      {
      	friend void cuff::snip(muff &);
      	...
      };
      
      class cuff
      {
      	public:
      		void snip(muff &) {...}
      		...
      };
      ```

      首先，`cuff`类声明应该在`muff`类之前，以便编译器可以理解`cuff::snip()`。其次，编译器需要`muff`的一个前向声明，以便可以理解`snip(muff &)`：

      ```
      class muff; // forward declaration
      class cuff
      {
      	public:
      		void snip(muff &) {...}
      		...
      };
      
      class muff
      {
      	friend void cuff::snip(muff &);
      	...
      };

2. **您知道了如何建立相互类友元的方法。能够创建一种更为严格的友情关系，即类B只有部分成员是类A的友元，而类A只有部分成员是类B的友元吗？请解释原因。**

   不能。为使类A拥有一个本身为类B的成员函数的友元，B的声明必须位于A的声明之前。一个前向声明是不够的，因为这种声明可以告诉A：B是一个类；但它不能指出类成员的名称。同样，如果B拥有一个本身为A的成员函数的友元，则这个A的声明必须位于B的声明之前。这两个要求是互斥的。

3. **下面的嵌套类声明中可能存在什么问题？**

   ```
   class Ribs
   {
   	private:
   		class Sauce
   		{
   			int soy;
   			int suger;
   			public:
   				Sauce(int s1, int s2) : soy(s1), suger(s2) {}
   		};
   		...
   };
   ```

   访问类的唯一方法是通过其公有接口，这意味着对于`Sauce`对象，只能调用构造函数来创建一个。其他成员（`soy`和`suger`）在默认情况下是私有的。

4. **`throw`和`return`之间的区别何在？**

   假设函数`f1()`调用函数`f2()`。`f2()`中的返回语句导致程序执行在函数`f1()`中调用`f2()`后面的一条语句。`throw`语句导致程序沿函数调用的当前序列回溯，直到找到直接或间接包含对`f2()`的调用的`try`语句块为止。它可能在`f1()`中、调用`f1()`的函数中或其他函数中。找到这样的`try`语句块后，将执行下一个匹配的`catch`语句块，而不是函数调用后的语句。

5. **假设有一个从异常基类派生来的异常类层次结构，则应按什么样的顺序放置`catch`块？**

   应按从子孙到祖先的顺序排列`catch`语句块。

6. **对于本章定义的`Grand`、`Superb`和`Magnificant`类，假设`pg`为`Grand *`指针，并将其中某个类的对象的地址赋给了它，而`ps`为`Superb *`指针，则下面两个代码示例的行为有什么不同？**

   ```
   if (ps == dynamic_cast<Superb *>(pg))
   	ps->say(); // sample #1
   if (typeid(*pg) == typeid(Superb))
   	(Superb *)pg->say(); // sample #2
   ```

   1. 对于示例#1，如果`pg`指向一个`Superb`对象或从`Superb`派生而来的任何类的对象，则`if`条件为`true`。具体地说，如果`pg`指向`Magnificant`对象，则`if`条件也为`true`
   2. 对于示例#2，仅当指向`Superb`对象时，`if`条件才为`true`，如果指向的是从`Superb`派生出来的对象，则`if`条件不为`true`

7. **`static_cast`运算符与`dynamic_cast`运算符有什么不同？**

   `dynamic_cast`运算符只允许沿类层次结构向上转换，而`static_cast`运算符允许向上转换和向下转换。`static_cast`运算符还允许枚举类型和整型之间以及数值类型之间的转换。



### 笔记

* 友元声明可以位于类的公有、私有和保护部分，其所在的位置无关紧要
* 内联函数的链接性是内部的，这意味着函数定义必须在使用函数的文件中。因此，将内联函数的定义放在头文件中可以确保将定义放在正确的地方
* 异常类型可以是字符串或其他C++类型，通常为类类型
* 执行`throw`语句类似于执行返回语句，因为它也将终止函数的执行；但`throw`不是将控制权返回给调用程序，而是导致程序沿调用序列后退，直到找到包含`try`块的函数
* 在默认情况下，如果函数引发了异常，而没有`try`块或没有匹配的处理程序时，程序最终将调用`abort()`函数，但可以修改这个默认行为
* 引发异常时编译器总是创建一个临时拷贝，即使异常规范和`catch`块中指定的是引用
  * `catch`引用的目的：基类引用可以匹配派生类引用
  * 在`catch`块捕获基类对象，而不是引用时，将捕获所有派生类对象，但只保留基类特性，因此只能使用虚方法的基类版本
  * 引发的异常对象将被第一个与之匹配的`catch`块捕获。这意味着`catch`块的排列顺序应该与派生顺序相反
* `catch(...)`可以捕获所有异常，类似`switch`的`default`
* RTTI只适用于包含虚函数的类
* 赋值表达式的值是左边的值





## 第16章 string类和标准模板库

1. **考虑下面的类声明：**

   ```
   class RQ1
   {
   	private:
   		char* st; // points to C-style string
   	public:
   		RQ1() { st = new char[1]; strcpy(st, ""); }
   		RQ1(const char* s) { st = new char[strlen(s) + 1]; strcpy(st, s); }
   		RQ1(const RQ1& rq) { st = new char[strlen(rq.st) + 1]; strcpy(st, rq.st); }
   		~RQ1() { delete[] st; }
   		RQ& operator=(const RQ& rq);
   		// more stuff
   };
   ```

   **将它转换为使用`string`对象的声明。哪些方法不再需要显式定义？**

   不再需要显式复制构造函数、析构函数和赋值运算符，因为`string`对象提供了自己的内存管理功能。

2. **在易于使用方面，指出`string`对象至少两个优于C风格字符串的地方。**

   * 可以将一个`string`对象赋给另一个
   * `string`对象提供了自己的内存管理功能，所以一般不需要担心字符串超出存储容量

3. **编写一个函数，用`string`对象作为参数，将`string`对象转换为全部大写。**

   ```
   #include <string>
   #include <cctype>
   using namespace std;
   void ToUpper(string& str)
   {
   	for(int i = 0; i < str.size(); i++)
   	{
   		str[i] = toupper(str[i]);
   	}
   }

4. **从概念上或语法上说，下面哪个不是正确使用`auto_ptr`的方法（假设已经包含了所需的头文件）？**

   ```
   auto_ptr<int> pia(new int[20]); // #1
   auto_ptr<string> (new string);  // #2
   int rigue = 7;
   auto_ptr<int> pr(&rigue);       // #3
   auto_ptr dbl(new double); 		// #4
   ```

   1. `auto_ptr`没有使用`new[]`的版本
   2. 没有定义指针名
   3. 不能指向栈内存
   4. 没有对指针类型进行实例化

5. **如果可以生成一个存储高尔夫球棍（而不是数字）的栈，为何它（从概念上说）是一个坏的高尔夫袋子？**

   栈的LIFO特征意味着可能必须在到达所需要的球棍（club）之前删除很多球棍。

6. **为什么说对于逐洞记录高尔夫成绩来说，`set`容器是糟糕的选择？**

   集合将只存储每个值的一个拷贝，因此，5个5分将被存储为1个5分。

7. **既然指针是一个迭代器，为什么STL设计人员没有简单地使用指针来代替迭代器呢？**

   使用迭代器使得能够使用接口类似于指针的对象遍历不以数组方式组织的数据，如双向链表中的数据。

8. **为什么STL设计人员仅定义了迭代器基类，而使用继承来派生其他迭代器类型的类，并根据这些迭代器来表示算法？**

   STL方法使得可以将STL函数用于指向常规数组的常规指针以及指向STL容器类的迭代器，因此提高了通用性。

9. **给出`vector`对象比常规数组方便的3个例子。**

   1. 可以将一个`vector`对象赋给另一个
   2. vector管理自己的内存，因此可以将元素插入到矢量中，并让它自动调整长度
   3. 使用`at()`方法，可以自动检查边界

10. **如果程序清单16.9是使用`list`（而不是`vector`）实现的，则该程序的哪些部分将是非法的？非法部分能够轻松修复吗？如果可以，如何修复呢？**

    这两个`vector`函数和`random_shuffle()`函数要求随机访问迭代器，而`list`对象只有双向迭代器。可以使用`list`模板类的`sort()`成员函数，而不是通用函数来排序，但没有与`random_shuffle()`等效的成员函数。然而，可以将链表复制到矢量中，然后打乱矢量，并将结果重新复制到链表中。

11. **假设有程序清单16.15所示的函数符`TooBig`，下面的代码有何功能？赋给`bo`的是什么值？**

    ```
    bool bo = TooBig<int>(10)(15);
    ```

    创建一个匿名的`TooBig`类型的函数符对象并以10初始化，调用其`operator()`运算符重载函数，以15为参数，`15 > 10`，因此返回true。



### 笔记

* 所有智能指针类都有一个`explicit`构造函数，该构造函数将指针作为参数。因此，不会自动将指针转换为只能指针对象
* 程序试图将一个`unique_ptr`赋给另一个时，如果源`unique_ptr`是个临时右值，编译器允许这样做；如果源`unique_ptr`将存在一段时间，编译器将禁止这样做。相对的，`auto_ptr`不会禁止这种操作，但可能导致运行阶段的程序崩溃（尝试释放已经被释放过的内存）
* 禁止（其实是建议，编译器并不禁止）在容器对象中使用`auto_ptr`，但允许使用`unique_ptr`
* `unique_ptr`有针对`new []`和`delete []`的版本，而`auto_ptr`没有
* 使用`new`分配内存时，才能使用`auto_ptr`和`shared_ptr`，使用`new []`分配内存时，不能使用它们。不使用`new`分配内存时，不能使用`auto_ptr`和`shared_ptr`；不使用`new`或`new []`分配内存时，不能使用`unique_ptr`
* 很多STL算法都支持复制和赋值操作，这些操作可用于`shared_ptr`，但不能用于`unique_ptr`（编译器发出警告）和`auto_ptr`（行为不确定）
* 在`unique_ptr`为右值时，可将其赋给`shared_ptr`，这与将一个`unique_ptr`赋给另一个需要满足的条件相同。模板`shared_ptr`包含一个显式构造函数，可用于将右值`unique_ptr`转换为`shared_ptr`。`shared_ptr`将接管原来归`unique_ptr`所有的对象
* `vector`模板使用动态内存分配，因此可以用初始化参数来指出需要多少矢量
* 迭代器是一个广义指针。事实上，它可以是指针，也可以是一个可对其执行类似指针的操作——如解除引用（如`operator*()`）和递增（如`operator++()`）——的对象
* **标准模板库：16.3**
* `for_each()`函数将被指向的函数应用于容器区间中的各个元素。被指向的函数不能修改容器元素的值
* `random_shuffle()`函数接受两个指定区间的迭代器参数，并随机排列该区间中的元素。与可用于任何容器类的`for_each()`不同，该函数要求容器类允许随机访问，如`vector`
* `sort()`函数也要求容器支持随机访问
  * 该函数的第一个版本接受两个定义区间的迭代器参数，并使用为存储在容器中的类型元素定义的`<`运算符，对区间中的元素进行操作（即升序）。如果容器元素是用户定义的对象，则要使用`sort()`，必须定义能够处理该类型对象的`operator<()`函数，才能使用这个函数版本
  * 如果想以其他方式排序（如降序），可以使用接受3个参数的版本，最后一个参数是指向要使用的函数的指针（函数对象），而不是`operator<()`。该函数的返回值需要能够转换为`bool`，`false`表示两个参数的顺序不正确
* 不同于`for_each()`，基于范围的`for`循环可以修改容器的内容，诀窍是指定一个引用参数
  * `for(auto & x : items) function(x);`：其中函数的参数为引用参数
* 模板使得算法独立于存储的数据类型，而迭代器使算法独立于使用的容器类型。它们都是STL通用方法的重要组成部分
* STL的迭代器
  * 每个容器类（`vector`、`list`、`deque`等）定义了相应的迭代器类型。对于其中的某个类，迭代器可能是指针；而对于另一个类，可能是对象
  * 每个容器类都有一个超尾标记，当迭代器递增到超越容器的最后一个值后，这个值将被赋给迭代器
  * 使用容器类时，无需知道其迭代器是如何实现的，也无需知道超尾是如何实现的，而只需知道它有迭代器，其`begin()`返回一个指向第一个元素的迭代器，`end()`返回一个指向超尾位置的迭代器即可
  * STL定义了5种迭代器，并根据所需的迭代器类型对算法进行了描述。这5种迭代器分别是输入迭代器、输出迭代器、正向迭代器、双向迭代器和随机访问迭代器
  * 对于输入迭代器，不能保证输入迭代器第二次遍历容器时，顺序不变。另外，输入迭代器被递增后，也不能保证其先前的值仍然可以被解除引用。基于输入迭代器的任何算法都应当是单通行（single-pass）的，不依赖于前一次遍历时的迭代器值，也不依赖于本次遍历中前面的迭代器值。注意，输入迭代器是单向迭代器，可以递增，但不能倒退
  * 输出迭代器与输入迭代器类似，只是解除引用让程序能够修改容器值，而不能读取。简而言之，对于单通行、只读算法，可以使用输入迭代器；而对于单通行、只写算法，可以使用输出迭代器
  * **迭代器各类型：16.4.2**
  * 根据特定迭代器类型编写的算法可以使用该种迭代器，也可以使用具有所需功能的任何其他迭代器
  * 迭代器概念具有类似继承的关系，然而，不能将C++继承机制用于迭代器。因为它在一个容器中可能是指针，而在另一个容器中是类
  * 迭代器是广义指针，而指针满足所有的迭代器要求。迭代器是STL算法的接口，而指针是迭代器，因此STL算法可以使用指针来对基于指针的非STL容器进行操作
* 数组名称也是数组第一个元素的地址；对数组名称取地址得到的是整个数组的地址
* 并非任何类型的对象都能存储在容器中，具体地说，类型必须是可复制构造的和可赋值的。基本类型满足这些要求；只要类定义没有将复制构造函数和赋值运算符声明为私有或保护的，则也满足这种要求。C++11改进了概念，添加了术语可复制插入（CopyInsertable）和可移动插入（MoveInsertable）
* **容器种类以及序列容器：16.4.5**
* `queue`模板类是一个适配器类，底层类默认为`deque`
* `priority_queue`和`stack`都是适配类，底层类默认为`vector`
* 模板类`array`并非STL容器，因为其长度是固定的。但可将很多标准STL算法用于`array`对象，如`copy()`和`for_each()`
* **关联容器：16.4.6**
* 关联容器（associative container）是对容器概念的另一个改进。关联容器将值与键关联在一起，并使用键来查找值
* 无序关联容器是对容器概念的另一种改进。与关联容器一样，无序关联容器也将值与键关联起来，并使用键来查找值。但底层的差别在于，关联容器是基于树结构的，而无序关联容器是基于数据结构哈希表的，这旨在提高添加和删除元素的速度以及提高查找算法的效率。
* **函数对象：16.5**
* 很多STL算法都使用函数对象——也叫函数符（functor）。函数符是可以以函数方式与`()`结合使用的任意对象。这包括函数名、指向函数的指针和重载了`()`运算符的类对象（即定义了函数`operator()()`的类）
* STL定义的函数符概念
  * 生成器（generator）是不用参数就可以调用的函数符
  * 一元函数（unary function）是用一个参数就可以调用的函数符
  * 二元函数（binary function）是用两个参数就可以调用的函数符
  * 改进版
    * 返回`bool`值的一元函数是谓词（predicate）
    * 返回`bool`值的二元函数是二元谓词（binary predicate）
* 对于算法函数设计，有两个主要的通用部分。首先，它们都使用模板来提供泛型；其次，它们都使用迭代器来提供访问容器中数据的通用表示
* 统一的容器设计使得不同类型的容器之间具有明显关系。例如，可用`==`来比较不同类型的容器，之所以能够这样做，是因为容器重载的`==`运算符使用迭代器来比较内容，若内容和排列顺序都相同，则它们是相等的
* **算法：16.6**
* STL将算法库分成4组：
  * `<algorithm>`
    * 非修改式序列操作
      * `finf()`
      * `for_each()`
    * 修改式序列操作
      * `transform()`
      * `random_shuffle()`
      * `copy()`
    * 排序和相关操作
      * `sort()`
      * 集合操作
  * `<numeric>`
    * 通用数字运算
* 使用STL时应尽可能减少要编写的代码。STL通用、灵活的设计将节省大量工作。另外，STL设计者就是非常关心效率的算法人员，算法是经过仔细选择的，并且是内联的
* **16.7其他库**
* STL是一个容器类模板、迭代器类模板、函数对象模板和算法函数模板的集合，它们的设计是一致的，都是基于泛型编程原则的。算法通过使用模板，从而独立于所存储的对象的类型；通过使用迭代器接口，从而独立于容器的类型。迭代器是广义指针



## 第17章 输入、输出和文件

1. **`iostream`文件在C++ I/O中扮演何种角色？**

   `iostream`文件定义了用于管理输入和输出的类、常量和操纵符，这些对象管理用于处理I/O的流和缓冲区。该文件还创建了一些标准对象（`cin`、`cout`、`cerr`和`clog`以及对应的宽字符对象），用于处理与每个程序相连的标准输入和输出流。

2. **为什么键入数字（如121）作为输入要求程序进行转换？**

   键盘输入生成一系列字符。输入121将生成3个字符，每个字符都由一个1字节的二进制码表示。要将这个值存储为`int`类型，则必须将这3个字符转换为121值的二进制表示。

3. **标准输出与标准错误之间有什么区别？**

   在默认情况下，标准输出和标准错误都将输出发送给标准输出设备（通常为显示器）。然而，如果要求操作系统将输出重定向到文件，则标准输出将与文件（而不是显示器）相连，但标准错误仍与显示器相连。

4. **为什么在不为每个类型提供明确指示的情况下，`cout`仍能够显示不同的C++类型？**

   `ostream`类为每种C++基本类型定义了一个`operator<<()`函数的版本。编译器将下面的表达式

   ```
   cout << spot
   ```

   解释为

   ```
   cout.operator<<(spot)
   ```

   这样，它便能够将该方法调用与具有相同参数类型的函数原型匹配。

5. **输出方法的定义的哪一特征让您能够拼接输出？**

   可以将返回`ostream &` 类型的输出方法拼接。这样，通过一个对象调用方法时，将返回该对象。然后，返回对象将可以调用序列中的下一个方法。

6. **编写一个程序，要求用户输入一个整数，然后以十进制、八进制和十六进制显示该整数。在宽度为15个字符的字段中显示每种形式，并将它们显示在同一行上，同时使用C++数基前缀。**

   ```
   // rq17-6.cpp
   #include <iostream>
   #include <iomanip>
   
   int main()
   {
   	using namespace std;
   	cout << "Enter an integer: ";
   	int n;
   	cin >> n;
   	cout << setw(15) << "base ten"
   		 << setw(15) << "base sixteen"
   		 << setw(15) << "base eight" << "\n";
   	cout.setf(ios::showbase); // or cout << showbase;
   	cout << setw(15) << n << hex << setw(15) << n << oct << setw(15) << n << "\n";
   	return 0;
   }

7. **编写一个程序，请求用户输入下面的信息，并按下面的格式显示它们：**

   ```
   Enter your name: Billy Gruff
   Enter your hourly wages: 12
   Enter number of hours worked: 7.5
   First format:
   				   Billy Gruff: $		12.00: 	7.5
   Second format:
   Billy Gruff					  : $12.00		 :7.5
   ```

   ```
   // rq17-7.cpp
   
   #include <iostream>
   #include <iomanip>
   
   int main()
   {
   	using namespace std;
   	char name[20];
   	float hourly;
   	float hours;
   	
   	cout << "Enter your name: ";
   	cin.get(name, 20).get();
   	cout << "Enter your hourly wages: ";
   	cin >> hourly;
   	cout << "Enter number of hours worked: ";
   	cin >> hours;
   	
   	cout.setf(ios::showpoint);
   	cout.setf(ios::fixed, ios::floatfield);
   	cout.setf(ios::right, ios::adjustfiled);
   	// or cout << showpoint << fixed << right;
   	cout << "First format:\n";
   	cout << setw(30) << name << ": $" << setprecision(2)
   		 << setw(10) << hourly << ":" << setprecision(1)
   		 << setw(5) << hours << "\n";
   	cout << "Second format:\n";
   	cout.setf(ios::left, ios::adjustfield);
   	cout << setw(30) << name << ": $" << setprecision(2)
   		 << setw(10) << hourly << ":" << setprecision(1)
   		 << setw(5) << hours << "\n";
   	return 0;
   }

8. **对于下面的程序：**

   ```
   // rq17-8.cpp
   #include <iostream>
   
   int main()
   {
   	using namespace std;
   	char ch;
   	int ct1 = 0;
   	
   	cin >> ch;
   	while(ch != 'q')
   	{
   		ct1++;
   		cin >> ch;
   	}
   	
   	int ct2 = 0;
   	cin.get(ch);
   	while(ch != 'q')
   	{
   		ct2++;
   		cin.get(ch);
   	}
   	cout << "ct1 = " << ct1 << "; ct2 = " << ct2 << "\n";
   	
   	return 0;
   }
   ```

   **如果输入如下，该程序将打印什么内容？**

   ```
   I see a q<Enter>
   I see a q<Enter>
   ```

   **其中，`<Enter>`表示回车键。**

   ```
   ct1 = 5; ct2 = 9
   ```

   该程序的前半部分忽略空格和换行符，而后半部分没有。注意，程序的后半部分从第一个q后面的换行符开始读取，将换行符计算在内。

9. **下面的两条语句都读取并丢弃行尾之前的所有字符（包括行尾）。这两条语句的行为在哪方面不同？**

   ```
   // #1
   while(cin.get() != '\n')
   	continue;
   // #2
   cin.ignore(80, '\n');
   ```
   
   如果输入行超过80个字符，`ignore()`将不能正常工作。在这种情况下，它将跳过前80个字符。



### 笔记

* C++用指向字符串存储位置的指针来表示字符串。指针的形式可以是`char`数组名、显式的`char`指针或用引号括起的字符串。方法使用字符串中的终止空字符来确定何时停止显式字符
* 对于其他类型的指针，C++将其对应于`void*`，并打印地址的数值表示。如果要获得字符串的地址，则必须将其强制转换为其他类型（如`void*`）
* 除了各种`operator<<()`函数外，`ostream`类还提供了`put()`方法和`write()`方法，前者用于显示字符，后者用于显示字符串。两个方法都返回调用它们的对象的引用，因此可以连续调用。需要注意的是，`write()`方法并不会在遇到空字符时自动停止打印字符，而只是打印指定数目的字符，即使超出了字符串的边界
* 通常，缓冲区为512字节或其整数倍。当标准输出连接的是硬盘上的文件时，缓冲可以节省大量的时间。然而，对于屏幕输出来说，填充缓冲区的重要性要低得多。因此，在屏幕输出时，程序不必等到缓冲区被填满。例如，将换行符发到缓冲区后，将重新刷新缓冲区。且多数C++实现都会在输入即将发生时刷新缓冲区
* 如果实现不能在所希望时刷新输出，可以使用两个控制符中的一个来强行进行刷新。控制符`flush`刷新缓冲区，而控制符`endl`刷新缓冲区，并插入一个换行符。事实上，控制符也是函数，`ostream`类通过重载`<<`运算符使得在插入运算符中使用即为调用该函数，即`flush(cout);`与`cout << flush;`等价
* **`cout`的格式化输出：17.2.4**
* 输出默认为右对齐
* `cin`或`cout`对象包含一个描述流状态（stream state）的数据成员（继承于`ios_base`）。流状态（被定义为`iostate`类型，而`iostate`是一种`bitmask`类型）由3个`ios_base`元素组成：`eofbit`、`badbit`和`failbit`，其中每个元素都是一位，可以是1（设置）或0（清除）。当`cin`操作到达文件末尾时，它将设置`eofbit`；当`cin`操作未能读取到预期的字符时，它将设置`failbit`。I/O失败（如试图读取不可访问的文件或试图写入开启写保护的磁盘），也可能将`failbit`设置为1。在一些无法诊断的失败破坏流时，`badbit`元素将被设置
* **`istream`类方法：17.3.3/17.3.4**
* `get(char &)`成员函数返回一个指向用于调用它的`istream`对象的引用；`get(void)`成员函数的返回类型为`int`（或某种更大的整型，这取决于字符集和区域）
* 对于读取整行的`get()`和`getline()`函数，`get()`将换行符留在输入流中，`getline()`则抽取并丢弃输入流中的换行符
* **文件I/O：17.4**
* 由于`ostream`是`ofstream`类的基类，因此可以使用所有的`ostream`方法，包括各种插入运算符定义、格式化方法和控制符
* 以默认方式打开文件进行输出时将自动把文件的长度截短为0，这相当于删除已有的内容（`ofstream`）
* 文件的`is_open()`较新方法除了能够检测到`good()`能够检测到的错误，还能检测到——试图以不合适的文件模式打开文件时失败
* `ios_base::out`本身将导致文件被截短，但与`ios_base::in`一起使用时，不会导致文件被截短。一些冲突的组合，如`ios_base::in|ios_base::trunc`，将禁止文件被打开，``is_open()``方法可以检测出这种故障
* `ios_base::ate`和`ios_base::app`都将文件指针指向打开的文件尾。二者的区别在于，`ios_base::app`，模式只允许将数据添加到文件尾，而`ios_base::ate`模式将指针放到文件尾
* setw()后面接一个控制符，如dec，会导致输出长度控制失效吗





## 第18章 探讨C++新标准





### 笔记

* C++11扩大了用大括号括起的列表（初始化列表）的适用范围，使其可用于所有内置类型和用户定义的类型（即类对象）。使用初始化列表时，可添加等号（=），也可不添加

* 如果类有将模板`std::initializer_list`作为参数的构造函数，则只有该构造函数可以使用列表初始化形式

* 为向后兼容，C++11仍允许使用0来表示空指针，因此表达式`nullptr == 0`为`true`，但使用`nullptr`而不是0提供了更高的类型安全。例如，可将0传递给接受`int`参数的函数，但如果视图将`nullptr`传递给这样的函数，编译器将此视为错误

* 基于程序员的编程体验和`BOOST`库提供的解决方案，C++11摒弃了`auto_ptr`，并新增了3种智能指针：`unique_ptr`、`shared_ptr`和`weak_ptr`，新增的智能指针都能与STL容器和移动语义协同工作

* 为解决普通枚举的问题，C++11新增了一种枚举。这种枚举使用`class`或`struct`定义。新枚举要求进行显式限定，以免发生名称冲突

* C++很早就支持对象自动转换，但自动类型转换可能导致意外转换的问题。为解决这种问题，C++引入了关键字`explicit`（用在声明中），以禁止单参数构造函数和转换函数导致的自动转换

  ```
  class Plebe
  {
  	explicit Plebe(double);
  	explicit operator int() const;
  }

* 类内成员初始化：可使用等号或大括号版本的初始化，但不能使用圆括号版本的初始化。使用类内初始化可避免在构造函数中编写重复的代码

* C++11新增了右值引用，这是使用`&&`表示的。右值引用可关联到右值，即可出现在赋值表达式右边，但不能对其应用地址运算符的值。右值包括字面常量（C风格字符串除外，它表示地址）、诸如`x + y`等表达式以及返回值的函数（条件是该函数返回的不是引用）

* 将右值关联到右值引用导致该右值被存储到特定的位置，且可以获取该位置的地址。也就是说，虽然不能将运算符`&`用于13等右值，但可将其用于右值引用。通过将数据与特定的地址关联，使得可以通过右值引用来访问该数据

* 可使用运算符`static_cast<>`将左值的对象的类型强制转换为右值，但C++11提供了一种更简单的方式——使用头文件`<utility>`中声明的函数`std::move()`

* 当使用`std::move`并进行赋值时，如果类没有定义移动赋值运算符，编译器将使用复制赋值运算符。如果也没有定义复制赋值运算符，将根本不允许上述赋值。对大多数程序员来说，右值引用带来的主要好处并非是编写使用右值引用的代码，而是能够使用利用右值引用实现移动语义的库代码

* 在原有4个特殊成员函数（默认构造函数、复制构造函数、复制赋值运算符和析构函数）的基础上，C++11新增了两个：移动构造函数和移动赋值运算符。这些成员函数在我们没有提供且代码需要使用时，编译器会为我们提供这些函数的默认版本。例外情况是，如果我们提供了析构函数、复制构造函数或复制赋值函数，编译器将不会自动提供移动构造函数和移动赋值运算符；如果我们提供了移动构造函数或移动赋值运算符，编译器将不会自动提供复制构造函数和复制赋值运算符

* 默认的移动构造函数和移动赋值运算符的工作方式与复制的默认版本类似，但对于要复制的类对象，优先调用其移动构造函数和移动赋值运算符，否则才调用复制构造函数和复制赋值运算符

* 当编译器因为某些原因不提供函数的默认版本时，可以使用关键字`default`显式地声明这些函数的默认版本：`SomeClass() = default;`。另一方面，关键字`delete`可用于禁止编译器使用特定方法：`SomeClass(const SomeClass &) = delete;`，这个方法和将函数放在`private`部分有相同的效果

* 在启用移动方法的同时禁用复制方法，将导致无法进行左值的复制构造函数（移动操作使用的右值引用只能关联到右值表达式）。反之，即在启用复制方法的同时禁用移动方法，则在进行右值的复制时将调用复制构造函数生成临时对象

* 关键字`default`只能用于6个特殊成员函数，但`delete`可用于任何成员函数

* **C++11类的新功能：18.3**

* 在C++11中，可使用虚说明符`override`指出要覆盖一个虚函数：将其放在函数列表后面。如果声明与基类方法不匹配，编译器将视为错误。此外，当想要禁止派生类覆盖特定的虚方法时，可在参数列表后加上`final`

* 说明符`override`和`final`并非关键字，而是具有特殊含义的标识符。这意味着编译器根据上下文确定它们是否有特殊含义；在其他上下文中，可将它们用作常规标识符，如变量名或枚举

* **Lambda函数：18.4**

* 仅当lambda表达式完全由一条返回语句组成时，自动类型推断才管用（相当与使用`decltype`根据返回值进行推断）；否则，需要使用新增的返回类型后置语法

  ```
  [](int x){ return x % 3 == 0; }
  [](double x) -> double{ int y = x; return x - y; }

* 

