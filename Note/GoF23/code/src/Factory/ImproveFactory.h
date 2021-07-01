
/**
 * @file ImproveFactory.h
 * @brief 工厂模式的改善版，提高封装性
 * @date 2021-7-1
 */

#ifndef IMPROVEFACTORY_H
#define IMPROVEFACTORY_H
#include <iostream>
using std::cout;
using std::string;
using std::endl;

namespace ImproveFactory{

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
    template<class AbstractProduct_t>
    class AbstractFactory
    {
    private:
        /* data */
    public:
        AbstractFactory(){}
        ~AbstractFactory(){}
        virtual AbstractProduct_t* CreateProduct() = 0;
    };
    
    /**
     * @brief 具体工厂类
     * @param AbstractProduct_t：抽象产品类型
     * @param ConcreteProduct_t：需要生产的具体产品类型
     */
    template<class AbstractProduct_t, class ConcreteProduct_t>
    class ConcreteFactory : public AbstractFactory< AbstractProduct_t >
    {
    private:
        /* data */
    public:
        ConcreteFactory(){}
        ~ConcreteFactory(){}
        virtual AbstractProduct_t* CreateProduct()
        {
            return new ConcreteProduct_t;
        }
    };
/*
    template<class AbstractProduct_t, class ConcreteProduct_t>
    AbstractProduct_t* ConcreteFactory<class AbstractProduct_t, class ConcreteProduct_t> :: CreateProduct()
    {
        return new ConcreteProduct_t;
    }
*/
    void TestImproveFactory();
}

#endif