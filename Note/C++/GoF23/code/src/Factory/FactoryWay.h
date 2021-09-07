
/**
 * @file FactoryWay.h
 * @brief 工厂方法模式实现头文件
 * @details 简单工厂模式的改善，增加了工厂类的抽象
 * @date 2021-7-1
 */

#ifndef FACTORYWAY_H
#define FACTORYWAY_H

///产品的声明和定义与简单工厂一致，偷个懒，直接包含头文件使用即可
#include "simpleFactory.h"
#include <iostream>
using std::cout;
using std::endl;

/*****************************工厂******************************************/
 
 /**
 * @brief 抽象工厂类
 * 实现工厂抽象，规范工厂创建产品的接口
 */
class AbstractFactory
{
private:
    /* data */
public:
    AbstractFactory(/* args */);
    virtual ~AbstractFactory();
    virtual AbstractProduct* CreateProduct() = 0;
};

/**
 * @brief 具体工厂类
 * 实现抽象工厂接口，用于创建具体的产品，与具体产品一一绑定
 */
class ConcreteFactoryA : public AbstractFactory
{
private:
    /* data */
public:
    ConcreteFactoryA(/* args */);
    virtual ~ConcreteFactoryA();
    virtual AbstractProduct* CreateProduct();

    ConcreteFactoryA(const ConcreteFactoryA& )
    {
        cout << "copy construct!" << endl;
    }
    ConcreteFactoryA(ConcreteFactoryA&&)
    {
        cout << "move construct!" << endl;
    }
};

class ConcreteFactoryB : public AbstractFactory
{
private:
    /* data */
public:
    ConcreteFactoryB(/* args */);
    virtual ~ConcreteFactoryB();
    virtual AbstractProduct* CreateProduct();
};


void TestFactoryWay();

#endif