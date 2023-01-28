# Tools
## 简介
（只有中文版）

这是给需要一些工具的人用的。我在里面放的`tools`文件夹内的内容为C++类，可以使用。而在外面的`main.cpp`则为测试用。

各个类介绍如下：

1. `matrix`类需要包含文件`matrix.cpp`（注意是`tools`目录下的）。这个类的功能是实现矩阵。目前实现了矩阵的加、减、乘、除运算（除法只能是对一个整数），还有返回转置矩阵的
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

2. `BigInt`类需要包含文件`BigInt.cpp`（同样注意是`tools`目录下的）。这个类的功能是实现大整型。它有以下构造函数：
```cpp
BigInt();//默认构造函数
BigInt(string& s);//用左值引用的string赋值
BigInt(string&& s);//用右值引用的string赋值
BigInt(long long _val);//用long long赋值（其他整型都会进行提升）
BigInt(const UnsignedBigInt&);//用左值引用的UnsignedBigInt赋值（稍后会讲）
BigInt(UnsignedBigInt&&) noexcept;//用右值引用的UnsignedBigInt赋值（稍后会讲）
```


`BigInt`类可以设置严格模式或非严格模式。模式由一个`BigInt::strict_type`的`enum`指定。这个`enum`的类型是`BigInt::modetype`，定义如下：
```cpp
// in class UnsignedBigInt
enum strict_mode : mode_type {
    UnsignedBigIntUnUseStrict,//非严格模式
    UnsignedBigIntUseStrict//严格模式
};
```
而`BigInt`类引用了相关内容：
```cpp
// in class BigInt
typedef UnsignedBigInt::strict_mode strict_mode;
typedef UnsignedBigInt::mode_type mode_type;
```
`BigInt`类的构造函数（默认构造函数和复制构造函数除外）后面可以指定严格模式或非严格模式，即：
```cpp
BigInt(string& s, bool _strict = UnsignedBigInt::default_strict_mode);
BigInt(string&& s, bool _strict = UnsignedBigInt::default_strict_mode);
BigInt(maxinteger_type _val, bool _strict = UnsignedBigInt::default_strict_mode);
```
如果不指定后面的参数，将自动设置为默认模式。默认模式由`UnsignedBigInt::default_strict_mode`指定。

对于一个`BigInt`类对象`a`（`a`为非`const`对象），有设置模式的函数：
```cpp
void set_strict(strict_mode _strict);
```
可以重新设置`a`的模式。

如果要查询一个`BigInt`类对象的模式，可以使用函数：
```cpp
strict_mode using_strict() const;
```
返回这个对象（可以是`const`的）的模式。

**模式用途**：设置严格模式可以检查并报错，非严格模式不会对任何函数、运算符或构造函数进行检查，如果出错，只会返回一个空的对象。以后的出错（对`UnsignedBigInt`对象也适用，后面详解）是指开启严格模式的情况下的报错，不再赘述。

**建议**：最好开启严格模式，否则必须自己检查错误。

注意构造函数如果采用`string`赋值，数据**必须保证没有任何非整数的字符，否则程序将抛出以下错误中的一个**：
```
UnsignedBigInt::UnsignedBigInt(string& s):find a char not number!;
UnsignedBigInt::UnsignedBigInt(string&& s):find a char not number!;
```
因为`BigInt`是采用`UnsignedBigInt`实现的，所以会在`UnsignedBigInt`类的构造函数里出错，不要惊讶。

同时程序会立即终止（崩溃）。

`BigInt`类还支持输出，如：
```cpp
BigInt a=string("123456789"),b=string("-123456789");
cout << a;//输出123456789
cout << b;//输出-123456789
```
以及输入，如：
```cpp
BigInt a;
cin >> a;//假设键入42
cout << a;//输出42
```
注意输入同样**在空白字符（换行、空格、Tab，等等）前不能有任何非整数的字符，否则程序将抛出以下错误中的一个（或多个）**：
```
istream& operator>>(istream& is, BigInt& a):Something wrong!
istream& operator>>(istream& is, BigInt&& a):Something wrong!
UnsignedBigInt::UnsignedBigInt(string& s):find a char not number!;
UnsignedBigInt::UnsignedBigInt(string&& s):find a char not number!;
```

同时传入的`istream`类参数会设置`failbit`，并将`BigInt`类参数赋值为0。

`BigInt`类也支持四则运算、取余运算和幂运算。如以下程序示范：
```cpp
BigInt a=string("1"),b=string("1");
cout << a+b;//输出2
cout << a-b;//输出0
cout << a*b;//输出1
cout << a/b;//输出1
cout << a%b;//输出0
```
但是幂运算的右操作数的类型不是`BigInt`，而是`BigInt::maxinteger_type`（保证为内置有符号整型）。程序示范如下：
```cpp
BigInt a=string("1");
BigInt::maxinteger_type b=5;
cout << a^b;//输出1
```
和`int`一样，除法运算自动向下取整。如果你尝试除以0，程序将抛出以下错误中的一个：
```
const UnsignedBigInt UnsignedBigInt::operator/(const UnsignedBigInt& a) const:Cannot with zero!
const UnsignedBigInt UnsignedBigInt::operator/(const UnsignedBigInt&& a) const:Cannot with zero!
```
同时程序会立即终止（崩溃）。

`BigInt`类支持大数的运算。如：
```cpp
cout << BigInt(4279853LL)*BigInt(432978237LL);//输出1853083206559161
```
如果尝试对0取余，程序将跑出以下错误中的一个：
```
const UnsignedBigInt UnsignedBigInt::operator%(const UnsignedBigInt& a) const:Cannot with zero!
const UnsignedBigInt UnsignedBigInt::operator%(const UnsignedBigInt& a) const:Cannot with zero!
```

`BigInt`类支持比较运算，包括`<`、`<=`、`>`、`>=`、`==`和`!=`。也就是说，你可以对一个元素为`BigInt`的数组进行排序，或者做别的事。

3. `UnsignedBigInt`类需要包含文件`BigInt.cpp`（同样注意是`tools`目录下的）。这个类的功能是实现无符号的大整型。它有以下构造函数：
```cpp
UnsignedBigInt();//默认构造函数
UnsignedBigInt(string& s);//用左值引用的string赋值
UnsignedBigInt(string&& s);//用右值引用的string赋值
UnsignedBigInt(unsigned long long _val);//用unsigned long long赋值（其他整型会被提升，有符号整型如果为负数，则会产生一些奇怪的结果
```
`UnsignedBigInt`类的功能大部分和`BigInt`类相同，可能抛出的错误也差不多。但是注意，如果**尝试用一个数去减比它小的数**（如1-2），**程序将会抛出以下错误中的一个**：
```
const UnsignedBigInt UnsignedBigInt::operator-(const UnsignedBigInt& a) const:(*this)<a not alivible!
const UnsignedBigInt UnsignedBigInt::operator-(const UnsignedBigInt&& a) const:(*this)<a not alivible!
```

还会有一些别的错误，主要是由于**用户尝试得到负数**导致的。

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

## 时间复杂度
对于一个长`n`宽`m`的`Matrix`类，大部分操作的时间复杂度都为O(nm)。但是求矩阵的迹（`const Int trace() const;`）的时间复杂度为O(n)。

对于一个长度为a的`UnsignedBigInt`类和一个长度为b的`UnsignedBigInt`类（a是左操作数，b是右操作数），执行加法、减法的时间复杂度为O(max(a,b))，执行乘法、除法、取余的时间复杂度为O(ab)。

对于一个长度为a的`UnsignedBigInt`类和一个`UnsignedBigInt::maxinteger_type`类型的数b，执行幂运算的时间复杂度为O(a^(lg b))。

## 注意事项

导入的时候请注意导入的后缀名为`.cpp`，这一点与标准库不同。

程序的报错会通过`cerr`进行，如果不想显示可以对`cerr`进行重定向。