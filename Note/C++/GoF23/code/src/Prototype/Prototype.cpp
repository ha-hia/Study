
/**
 * @file Prototype.cpp
 * @brief 原型模式实现cpp文件
 * @details 
 * @date 2021-6-30
 */

#include "Prototype.h"
#include <iostream>

/**
 * @brief 实现基类的 clone 方法，内部调用拷贝构造函数
 * 疑问：直接使用拷贝构造函数也可以用已有对象生成一个新的对象，为什么还要在外部封一个 clone？
 * 比较：原型模式是实现的 clone 接口，基于多态的 Clone 虚函数。在继承场景下，Clone 函数可以定义为虚函数。
 *      也就是说原型模式能够通过基类指针来复制派生类对象。拷贝构造函数完不成这样的任务。
 * 注意：由于是调用了拷贝构造函数，因此，对于复制生成新对象的需求不一，需要考虑深拷贝和浅拷贝的情况！！！
 */
ConcreteProto* ConcreteProto::clone()
{
    ConcreteProto* copyElement = new ConcreteProto(*this);
    return copyElement;
}

void TestPrototype()
{
    using namespace std;
    ConcreteProto* oldP = new ConcreteProto(0);
    ConcreteProto* newP = oldP->clone();

    if ( oldP->GetStatusForTest() == newP->GetStatusForTest() )
    {
        cout << "TestPrototype IS OK" << endl;
    }
    else
    {
        cout << "TestPrototype IS FAIL" << endl;
    }
    delete newP;
    newP = nullptr;

    delete oldP;
    oldP = nullptr;

}