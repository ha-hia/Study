
/**
 * @file AbstractFactory.h
 * @brief 抽象工厂模式实现头文件
 * @details 工厂方法模式的提升，一个功能能实现同一产品族的不同级别产品
 * @date 2021-7-1
 */

#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
#include <iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;


/**
 * @brief 抽象产品类
 * 提供规范接口，确定产品属性
 */
namespace Abstract {

    /*****************************产品******************************************/
    class AbstractProductA
    {
    private:

    public:
        AbstractProductA(){}
        virtual ~AbstractProductA(){}
        virtual void ShowName() = 0;
    };

    /**
     * @brief 具体产品类
     * 实现抽象产品类接口，创建具体产品
     */
    class ProductA : public AbstractProductA
    {
    private:
        /* data */
        std::string m_productName;
    public:
        ProductA() : m_productName("ProductA")
        {}
        ~ProductA(){}
        virtual void ShowName()
        {
            cout << m_productName << endl;
        }
    };


    class AbstractProductB
    {
    private:

    public:
        AbstractProductB(){}
        virtual ~AbstractProductB(){}
        virtual void ShowName() = 0;
    };

    /**
     * @brief 具体产品类
     * 实现抽象产品类接口，创建具体产品
     */
    class ProductB : public AbstractProductB
    {
    private:
        /* data */
        std::string m_productName;
    public:
        ProductB() : m_productName("ProductB")
        {}
        ~ProductB()
        {}
        virtual void ShowName()
        {
            cout << m_productName << endl;
        }
    };
    /*****************************工厂******************************************/
    
    /**
     * @brief 抽象工厂类
     * 实现工厂抽象，规范工厂创建产品的接口,创建不同产品
     */
    class AbstractFactory
    {
    private:
        /* data */
    public:
        AbstractFactory(/* args */){}
        virtual ~AbstractFactory(){}
        virtual AbstractProductA* CreateProductA() = 0;
        virtual AbstractProductB* CreateProductB() = 0;
    };

    class ConcreteFactoryNike : public AbstractFactory
    {
    private:
        /* data */
    public:
        ConcreteFactoryNike(/* args */){}
        ~ConcreteFactoryNike(){}
        AbstractProductA* CreateProductA();
        AbstractProductB* CreateProductB();
    };

    void TestAbstractFactory();

}



#endif