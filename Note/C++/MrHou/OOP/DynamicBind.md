## 动态绑定（Dynamic Bind）
### 条件：
1. 使用时，为指针变量
2. 指针变量所指向的变量支持向上装换（up-cast）
3. 指针调用的为虚函数

```C++
class A
{
    ...
    virtual test();
}

class B : public A
{
    ...
    virtual test();
}

A* ptr = new B;
ptr->test();//动态绑定 B::test();
```

### this指针
对象调用函数时，函数往往隐藏一个称为“this指针”的参数，意为调用该函数的对象的地址。

因此，对于以上例子实际底层的实现如下
```C++
ptr->test(); => (* (ptr->vptr)[n])(ptr)
                (* ptr->vptr[n])(ptr)
/*
1.通过ptr指针找到对象中的虚指针
2.在通过虚指针找到虚函数变中的第n(假设)个虚函数当作函数指针来调用
3.由于ptr本身即为指针，所以调用函数时传入的隐藏this指针就是ptr,
*/
```