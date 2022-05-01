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

