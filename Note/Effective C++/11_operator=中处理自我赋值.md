## 条款11：`operator=` 中处理自我赋值
场景：发生在对象被赋值给自己

```C++
class BitMap{...};
class Widget
{
    ...
private:
    BitMap* pb;
}

//危险版本
Widget& Widget::operator=(const Widget& rhs)
{
    delete pb;//释放当前pb的内容
    pb = new BitMap(*rhs.pb);//指向新的
    return *this;
}
//rhs和*this可能为同一个对象，delete pb可能就会销毁rhs对象的bitmap
//最后导致返回一个指向已经被删除对象的指针。

//正确版本  加入是否是同一对象的认证条件
Widget& Widget::operator=(const Widget& rhs)
{
    if(*this == rhs)
        return *this;

    delete pb;
    pb = new BitMap(*rhs.pb);
    return *this;
}

//当new BitMap产生异常(内存不足或对应的拷贝构造函数抛出异常)
//上述正确版本将使得对象持有一个野指针
//改善版本：提高“异常安全性”
Widget& Widget::operator=(const Widget& rhs)
{
    BitMap* ptrTemp = pb;//保留原先的pb
    pb = new BitMap(*rhs.pb);//指向新的，交换数据
    delete ptrTemp;//删除原先的
    return *this;
}

```