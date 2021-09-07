## const 用途  
1. 用于指针、引用、迭代器上  
2. 用于指针、引用、迭代器所指的对象上  
3. 用于函数参数和返回类型  
4. 用于局部变量  
5. 用于成员函数上
### const 修饰指针
| 与 * 的位置 |       含义     |  
|:-----------|:------------------:| 
| T const *ptr | 指针所指向的常量，其值不可变，但可以改变指针的值指向新的常量 | 
| const T *ptr | 同上 | 
| T* const ptr | 指针自身是常量不能改变指向，但所指向物体的值可以被改变 | 
| const T * const ptr | 表示指针本身以及所指物两者都是常量 | 

### const 修饰迭代器
迭代器是以指针为根据，声明迭代器为`const`就像声明指针为`const`一样(即声明`T* const` 指针一样)。  
```C++
const vector<int>::iterator it; => int* const it;
```
`const_iterator` ：STL提供的常量迭代器，确保迭代器所指的东西不可被改变  
```C++
  const vector<int>::iterator it1 = vec.begin();  
  *it1 = 10;//OK
  ++it1;//Error
  vector<int>::const_iterator it2 = vec.begin();  
  *it2 = 10;//Error
  ++it2;//OK  
```
### const 成员函数
#### 目的：  
* 确保该成员函数可以被const 对象调用，使**操作 const 对象**成为可能  。
* 使类的接口更容易被理解，知道哪个函数不可以改动对象内容。
* 当成员函数的const和non-const版本同时存在；const对象只能调用const版本，non-const对象只能调用non-const版本
* non-const对象可以调用const成员函数和非const成员函数

根据`Effective C++条款3`中说道，const成员函数分为位常量 "bitwise/physical constness" 与逻辑常量 "logical constness" 两方面，**编译器强制执行位常量但在编写程序时应该会用逻辑常量**

#### 位常量  
成员函数只有在不更改对象的任何成员变量的情况下才能说是const，也是C++对常量性的定义。但往往也存在例外，
``` C++
class Test{
  public:
  char& operator[](int size) const
  {
    return text[size];
  }
  private:
  char* text;
}

const Test a("hello");//常量对象
char *ptr = &a[0];//调用常量成员函数
*ptr = 'H';//这时a的内容变成了Hello
```
该程序中，调用 const 成员函数确实是没有改变对象的成员数据text，所以通过了编译器的bitwise测试，但最后还是通过了外部手段改变了text的值。

#### 逻辑常量

认为const成员函数可以修改对象内的某些bits，但只有在客户端侦测不出的情况下才得如此。

方式：声明成员变量时在前面加上 **mutable** 释放掉成员变量的bitwise constnes约束。

### const 和 non-const 成员函数中避免重复
当 const 和 non-const 成员函数有着实质等价的实现时，令 non-const 版本调用 const 版本可避免代码重复。反之，const 版本调用 non-const 版本则错误。

|                |  const对象(数据不可改变)  |  非const对象(数据可改变)  |
|:-----------    |:------------------------:| :---------------------:| 
|  const成员函数  |         可              |         可               | 
| 非const成员函数 |         不可              |        可               | 