
/**
 * @file Prototype.h
 * @brief 原型模式实现头文件
 * @details 原型接口 + 具体原型
 * @date 2021-6-30
 */

#ifndef PROTOTYPR_H
#define PROTOTYPR_H
#include <iostream>
#include <string>

 /**
 * @brief 原型接口
 */
class Prototype
{
private:
    /* data */
public:
    Prototype(){}
    virtual ~Prototype(){}

    virtual Prototype* clone() = 0;
};

 /**
 * @brief 具体原型类
 * 1. 实现 clone 接口
 * 2. 重载具体原型类的拷贝构造函数，将在 clone 内部被调用以复制新的对象
 */
class ConcreteProto : public Prototype
{
private:
    int status;
    std::string name;
public:
    ConcreteProto(){}
    virtual ~ConcreteProto(){}
    ConcreteProto(int inStatus)
    {
        status = inStatus;
    }
    ConcreteProto(const ConcreteProto& rvalue)
    {
        this->status = rvalue.status;
    }

    virtual ConcreteProto* clone();

    /**
     * 可以通过添加一些具体原型需要的函数在复制生成新对象后，为新对象修改相应的属性
     * 以下只是做个例子
    */
    void SetName(std::string inName);

    int GetStatusForTest()
    {
        return status;
    }

};

void TestPrototype();



#endif