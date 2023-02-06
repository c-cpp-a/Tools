# Tools
## 置顶消息
这个`README.md`已经不是最新的了，因为这个写工具库的人懒得更新。征求一位共同开发者，负责写外面的`README.md`。

## 简介
（只有中文版）

这是给需要一些工具的人用的。下面是对各个文件的功能详述：

1. `matrix.cpp`里面有`matrix`类。这个类的功能是实现矩阵。目前实现了矩阵的加、减、乘、除运算（除法只能是对一个整数），还有返回转置矩阵的
```cpp
const Matrix<Int> transpose() const;
```
以及对矩阵求矩阵的迹（注意如果大小不是`N*N`的会出错）：
```cpp
const Int trace() const;
```
如果你需要将矩阵的元素改成其他的，请使用模板类
```cpp
template <typename Int> class Matrix;
```
其中的`Int`即为元素类型。要求支持四则运算。

2. `BigInt.cpp`里面包含`UnsignedBigInt`类和`BigInt`类。其中`BigInt`类由`UnsignedBigInt`类实现。请注意，严格模式（后面有介绍）开启后，程序如果出错就会抛出一些错误信息（以`cerr`进行），并抛出`exception()`异常。对于一些普通函数，请注意其声明后面的注释，这个注释是用于说明功能的。

- `UnsignedBigInt`类是无符号大整型类。构造函数：
```cpp
UnsignedBigInt();
UnsignedBigInt(string& s, mode_type _strict = default_strict_mode);
UnsignedBigInt(string&& s, mode_type _strict = default_strict_mode);
UnsignedBigInt(const maxinteger_type _val,
               mode_type _strict = default_strict_mode);
UnsignedBigInt(const vector<value_type>& val,
               mode_type _strict = default_strict_mode);
UnsignedBigInt(const vector<value_type>&& val,
               mode_type _strict = default_strict_mode);
```
从中可以看到，`UnsignedBigInt`类可以由`string`构造，也可以由`const UnsignedBigInt::maxinteger_type`类型构造，或者由`vector<UnsignedBigInt::value_type>`构造。具体地，`string`会被逐个字符转化为数字并被存储起来；`const UnsignedBigInt::maxinteger_type`会被按照十进制的解释被存储起来；`vector<UnsignedBigInt::value_type>`会被按照下标解释为顺序的数字并被存储起来。

至于除了默认构造函数以外，所有的构造函数后面都可以附加一项`mode_type`的数字，指出是否开启严格模式。具体地，`mode_type`被定义为一个`typedef`，而以`mode_type`为存储类型的`enum`是`strict_mode`，其中储存着的就是指出是否开启严格模式的两种状态。

`UnsignedBigInt`类有完整的重载函数，使之可以处理基本的运算，具体地，`UnsignedBigInt`类重载了：`+`、`-`、`*`、`/`、`%`，以及流运算符和幂运算`^`。对于所有运算符重载，都有其累积形式（如`+=`、`-=`）。当然，流运算符并没有此类重载。目前正在试验`qpow`外部函数，请不要尝试。

由于`UnsignedBigInt`是无符号的，所以无法处理负数。每当使用时遇到负数，`UnsignedBigInt`均会抛出异常。

- `BigInt`是有符号大整型类。构造函数：
```cpp
BigInt();
BigInt(string& s, mode_type _strict = UnsignedBigInt::default_strict_mode);
BigInt(string&& s, mode_type _strict = UnsignedBigInt::default_strict_mode);
BigInt(maxinteger_type _val,
       mode_type _strict = UnsignedBigInt::default_strict_mode);
BigInt(const UnsignedBigInt&);
BigInt(UnsignedBigInt&&) noexcept;
```
能够看到，`BigInt`类比`UnsignedBigInt`类多了可以接受一个`UnsignedBigInt`类参数的构造函数。

`BigInt`类的功能与`UnsignedBigInt`类是大致相同的，具体可以参阅相关程序。

- **注：**本文经过重写，漏掉了某些函数。对于更多有用的函数，可以参阅相关文档。
4. `maths.h`是数学库，可以对`BigInt`类和`UnsignedBigInt`类做开平方根的运算，以及对`BigInt`类做绝对值的运算。开平方根的运算的调用方法是：
```cpp
Sqrt(a);//返回a的平方根，误差不超过1。
```
**如果尝试对一个负数开平方根，程序将抛出以下错误**：
```
BigInt Sqrt(const BigInt x):Cannot do sqrt() with x<0!
```
求绝对值的调用方法是：
```cpp
Abs(a);//返回a的绝对值，仅适用于BigInt类
```
因为`UnsignedBigInt`类是无符号类，本身就是正数，所以不用求绝对值。

同时这里有一些函数工具：

- `Code`命名空间中储存了加密解密的函数，需要包含`code.cpp`。其中实现了4个函数：
```cpp
const std::string decode_base64(const std::string&); //用base64解码，返回
void decode_base64_this(std::string&); //用base64解码，原地操作
const std::string encode_base64(const std::string&); //用base64加密，返回
void encode_base64_this(std::string&); //用base64加密，原地操作
```
从注释中可以得知它们是用于`base64`编码的加密解密的。注意如果其中发生错误，程序会抛出类型为`Code::base64_error`的错误，成员`what`指出了具体错误。

## 版本更新

--snip--

2022/12/21: 已经添加了除法运算。现在正在尝试对`BigInt`类和`UnsignedBigInt`类做开平方根的运算。有知道代码的可以联系我。

2022/12/22: 
1. 修正一点小错误。
2. 已经可以对`BigInt`类和`UnsignedBigInt`类做开平方根的运算了。
3. 添加了`BigInt`类和`UnsignedBigInt`类的取余运算。

2022/12/28:添加了`Code`函数工具命名空间，用于密码。

2023/1/3:放松了`matrix`类相乘的限制，现在一个`N`行`L`列的矩阵可以乘以一个`L`行`M`列的矩阵，不再要求`N`和`M`相等。

2023/1/28:
1. 添加了`BigInt`类和`UnsignedBigInt`类的是否严格模式的设置。
2. 添加分数模板类`Fraction`，但未实现其功能。

2023/2/5:
1. 实现了分数模板类`Fraction`的部分构造函数，但开发方向可能不在这上面。
2. 修复了若干`BigInt`类的bug，并采取新的测试方式。

2023/2/6:
1. 对`README.md`进行了结构调整，现在结构相当清晰。
2. 错误的显示方式已经模板化。

## 时间复杂度
对于一个长`n`宽`m`的`Matrix`类，大部分操作的时间复杂度都为O(nm)。但是求矩阵的迹（`const Int trace() const;`）的时间复杂度为O(n)。

对于一个长度为a的`UnsignedBigInt`类和一个长度为b的`UnsignedBigInt`类（a是左操作数，b是右操作数），执行加法、减法的时间复杂度为O(max(a,b))，执行乘法、除法、取余的时间复杂度为O(ab)。

对于一个长度为a的`UnsignedBigInt`类和一个`UnsignedBigInt::maxinteger_type`类型的数b，执行幂运算的时间复杂度为O(a^(log b))。

## 注意事项

导入的时候请注意导入的后缀名为`.cpp`，这一点与标准库不同。

程序的报错会通过`cerr`进行，如果不想显示可以对`cerr`进行重定向。