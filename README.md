# Tools
## 简介
（只有中文版）

这是给需要一些工具的人用的。我在里面放的`tools`文件夹内的内容为C++类，可以使用。而在外面的`main.cpp`则为测试用。

各个类介绍如下：

- `matrix`类需要包含文件`matrix.cpp`（注意是`tools`目录下的）。实现了矩阵的加、减、乘、除运算（除法只能是对一个整数），还有返回转置矩阵的
```cpp
const Matrix<Int> transpose() const;
```
如果你需要将矩阵的元素改成其他的，请使用模板类
```cpp
template <typename Int> class Matrix;
```
其中的`Int`即为元素类型。要求支持四则运算。

- `maths`是数学库，里面没什么东西，不讲解（速度没有标准库快）。

- `BigInt`和`UnsignedBigInt`类需要包含文件`BigInt.cpp`（同样注意是`tools`目录下的）。实现了大整数的加、减、乘运算和输入输出。其中`BigInt`类是有符号的大整型，`UnsignedBigInt`类是无符号的大整型。它们支持使用`string`构造，如：
```cpp
BigInt a=string("-123456789");
UnsignedBigInt b=string("123456789");
```
也支持强制转换为`string`类型。

此外，这两个类也支持强制转换为`bool`类型。
