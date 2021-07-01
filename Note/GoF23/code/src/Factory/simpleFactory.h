
/**
 * @file simpleFactory.h
 * @brief 简单工厂模式实现头文件
 * @details
 * @date 2021-7-1
 */

#ifndef SIMPLEFACTORY_H
#define SIMPLEFACTORY_H
#include <iostream>

namespace ProductType{
    enum TYPE{
        TYPEA,
        TYPEB
    };
}

 /**
 * @brief 抽象产品类
 * 提供规范接口，确定产品属性
 */
class AbstractProduct
{
private:

public:
    AbstractProduct();
    virtual ~AbstractProduct();
    virtual void ShowName() = 0;
};

 /**
 * @brief 具体产品类
 * 实现抽象产品类接口，创建具体产品
 */
class ConcreteProductA : public AbstractProduct
{
private:
    /* data */
    std::string m_productName;
public:
    ConcreteProductA(/* args */);
    ~ConcreteProductA();
    virtual void ShowName();
};

class ConcreteProductB : public AbstractProduct
{
private:
    /* data */
    std::string m_productName;
public:
    ConcreteProductB(/* args */);
    ~ConcreteProductB();
    virtual void ShowName();
};

/**
 * @brief 简单工厂类
 * 内部实现创建具体产品逻辑，根据用户输入创建相应产品
 * 客户无需知道对象创建的细节
 */
class SimpleFactory
{
private:
    /* data */
public:
    SimpleFactory();
    ~SimpleFactory();
    static AbstractProduct* CreateProduct(ProductType::TYPE productType);
};


void TestSimpleFactory();


#endif