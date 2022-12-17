# Tools
## 简介
（只有中文版）

这是给需要一些工具的人用的。我在里面放的`tools`文件夹内的内容为C++类，可以使用。而在外面的`main.cpp`则为测试用。

各个类介绍如下：

1. `matrix`类需要包含文件`matrix.cpp`（注意是`tools`目录下的）。这个类的功能是实现矩阵。目前实现了矩阵的加、减、乘、除运算（除法只能是对一个整数），还有返回转置矩阵的
```cpp
const Matrix<Int> transpose() const;
```
如果你需要将矩阵的元素改成其他的，请使用模板类
```cpp
template <typename Int> class Matrix;
```
其中的`Int`即为元素类型。要求支持四则运算。

2. `maths`是数学库，里面没什么东西，不讲解（速度没有标准库快）。

3. `BigInt`类需要包含文件`BigInt.cpp`（同样注意是`tools`目录下的）。这个类的功能是实现大整型。它有以下构造函数：
```cpp
BigInt();//默认构造函数
BigInt(string& s);//用左值引用的string赋值
BigInt(string&& s);//用右值引用的string赋值
BigInt(long long _val);//用long long赋值（其他整型都会进行提升）
BigInt(const UnsignedBigInt&);//用左值引用的UnsignedBigInt赋值（稍后会讲）
BigInt(UnsignedBigInt&&);//用右值引用的UnsignedBigInt赋值（稍后会讲）
```
注意如果采用`string`赋值，数据**必须保证没有任何非整数的字符，否则程序将抛出以下错误中的一个**：
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
注意输入同样**在空白字符（换行、空格、Tab，等等）前不能有任何非整数的字符，否则程序将抛出以下错误中的一个**：
```
istream& operator>>(istream& is, BigInt& a):Something wrong!
istream& operator>>(istream& is, BigInt&& a):Something wrong!
UnsignedBigInt::UnsignedBigInt(string& s):find a char not number!;
UnsignedBigInt::UnsignedBigInt(string&& s):find a char not number!;
```

同时程序会立即终止（崩溃）。

`BigInt`类也支持四则运算（除法还未实现）。如以下程序示范：
```cpp
BigInt a=stirng("1"),b=string("1");
cout << a+b;//输出2
cout << a-b;//输出0
cout << a*b;//输出1
```
`BigInt`类支持大数的运算（除法除外）。如：
```cpp
cout << BigInt(4279853LL)*BigInt(432978237LL);//输出1853083206559161
```

`BigInt`类支持比较运算，包括`<`、`<=`、`>`、`>=`、`==`和`!=`。也就是说，你可以对一个元素为`BigInt`的数组进行排序，或者做别的事。

- `UnsignedBigInt`类需要包含文件`BigInt.cpp`（同样注意是`tools`目录下的）。这个类的功能是实现无符号的大整型。它有以下构造函数：
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

