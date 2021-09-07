## 条款10：`operator=` 返回一个`*this`引用
赋值采用右结合律  
目的：为实现连续赋值，所有用于赋值相关的运算必须返回一个指向操作符左侧实参的引用。

``` C++
    Widget& operator=(const Widget& rhs) {
        ...
        return *this;
    }

    Widget& operator+=(const Widget& rhs) {
        ...
        return *this;
    }
    ///同样，也适用于-=,*=等
```

## 条款11：`operator=` 中处理自我赋值
场景：发生在对象被赋值给自己
