
#include "Builder.h"
#include <memory>
using std::shared_ptr;
using namespace std;

AbstractBuilder::AbstractBuilder()
{
    m_product = new Product;
}
AbstractBuilder::AbstractBuilder(Product* input) : m_product(input)
{

}

AbstractBuilder::~AbstractBuilder()
{
    delete m_product;
}
Product* AbstractBuilder::GetProduct()
{
    return m_product;
}

void ConcreteBuilderA::BuildPartA()
{
    m_product->SetPartA();
}
void ConcreteBuilderA::BuildPartB()
{
    m_product->SetPartB();
}

void Product::showInfo()
{
    cout << "Builder Test:" << " ";
    cout << partA << " " << partB << endl;
}

Director::Director() : m_abstractBuilder(nullptr)
{

}
Director::Director(AbstractBuilder* input) : m_abstractBuilder(input)
{

}
Director::~Director()
{
    delete m_abstractBuilder;
}

/**
 * @brief 获得组合的复杂对象
 * @details 内部逻辑负责如何组织子模块的组合，并返回组合的对象
 */
Product* Director::CreateProduct()
{
    m_abstractBuilder->BuildPartA();
    m_abstractBuilder->BuildPartB();
    return m_abstractBuilder->GetProduct();
}


void TestBuilder()
{
    /*
    shared_ptr<AbstractBuilder> abcBuilder( new ConcreteBuilderA );
    Director* p = new Director(abcBuilder);
    shared_ptr<Director> director = p;
    shared_ptr<Product> newProduct = director->CreateProduct();
    newProduct->showInfo();
*/


    AbstractBuilder* abcBuilder = new ConcreteBuilderA;
    Director* director = new Director(abcBuilder);
    Product* newProduct = director->CreateProduct();
    if(newProduct == nullptr)
    {
        cout << "OK" << endl;
    }
    newProduct->showInfo();
}

