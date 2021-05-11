## Since C++11
### 1、数量不定的模板参数
C++20之前编写模板时，有多少参数就要声明多少个形参，新特性之后支持多个参数的省略。

**"..."** 就是一个所谓的包 pack
1. 用于模板参数，就是模板参数包
2. 用于函数参数类型，就是函数参数类型包
3. 用于函数参数，就是函数参数包
```C++
void print()
{
    cout << "打印完成" << endl;
}

///注意“...”符号，已经纳入语法范畴
template <typename T,typename... Type>//模板参数包
void print(const T& first, const Type&... args)//函数参数类型包
{
    cout << "当前元素：" << first;
    cout << " ,剩余元素数量：" << sizeof...(args) << endl;
    print(args...);//函数参数包
}


int main()
{
    print(1, "+", 1, ">", 2);
    cin.get();
}

****************************
当前元素：1 ,剩余元素数量：4
当前元素：+ ,剩余元素数量：3
当前元素：1 ,剩余元素数量：2
当前元素：> ,剩余元素数量：1
当前元素：2 ,剩余元素数量：0
打印完成
****************************
```

### 2、基于范围的循环
语法格式：

    for(par : container)
    {...}

```C++
vector<int> Collect{ 1,2,3,4,5 };
for (auto i : Collect)//按值传递
{
    i += 1;
}
for (auto i : Collect)
{
    cout << i << " ";
}
cout << endl;
for (auto& i : Collect)//按引用传递
{
    i += 1;
}
for (auto i : Collect)
{
    cout << i << " ";
}
cout << endl;

****************************
1 2 3 4 5
2 3 4 5 6
****************************
```
