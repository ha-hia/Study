
/**
 * @file Builder.h
 * @brief 建造者模式实现头文件
 * @details 
 * 将复杂对象分解成各简单子对象，然后按相应的步骤组合成复杂对象（步骤一般固定）
 * 子对象实现灵活，所以相同的创建流程达到不同的表现，将构建与实现分离
 * @date 2021-7-2
 */
#ifndef BUILDER_H
#define BUILDER_H
#include <iostream>
using std::string;
using std::cout;
using std::endl;

class Product;

/**
 * @brief 抽象建造者类
 * @details 定义创建子部件的接口，具体实现由具体建造者类实现
 */
class AbstractBuilder
{
protected:
    Product* m_product;
public:
    AbstractBuilder();
    AbstractBuilder(Product* input);
    ~AbstractBuilder();
    virtual void BuildPartA(){}
    virtual void BuildPartB(){}
    Product* GetProduct();
};

/**
 * @brief 具体建造者类
 * @details 实现构建产品各个子部件的方法
 */
class ConcreteBuilderA : public AbstractBuilder
{
private:
    /* data */
public:
    ConcreteBuilderA()
    {
        
    }
    ~ConcreteBuilderA(){}

    void BuildPartA();
    void BuildPartB();
};

/**
 * @brief 产品类
 * @details 各个子模块组合成的复杂对象
 */
class Product
{
private:
    string partA;
    string partB;
public:
    Product()
    {
        
    }
    ~Product(){}
    void SetPartA(string str = "PartA"){
        partA = str;
    }
    void SetPartB(string str = "PartB"){
        partB = str;
    }
    void showInfo();
};

/**
 * @brief 指挥者类
 * @details 负责各子模块如何组合成复杂模块
 */
class Director
{
private:
    AbstractBuilder* m_abstractBuilder;
public:
    Director();
    Director(AbstractBuilder* input);
    ~Director();
    Product* CreateProduct();
};

void TestBuilder();

#endif
