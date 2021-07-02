
#include "Builder.h"
#include <memory>
using std::shared_ptr;
using namespace std;

AbstractBuilder::AbstractBuilder() : m_product(nullptr)
{
    cout << "AbstractBuilder" << endl;
    if (m_product == nullptr)
    {
        cout << "1" << endl;
    }
    else
    {
        cout << "0" << endl;
    }
    
}
AbstractBuilder::AbstractBuilder(Product* input) : m_product(input)
{
    if (nullptr == m_product)
    {
        cout << "null" << endl;
    }
    else
        cout << "not null" << endl;
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
    cout << "PartA" << " " << "PartB" << endl;
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
Product* Director::CreateProduct()
{
    Product* temp =  m_abstractBuilder->GetProduct();
    if (temp == nullptr)
    {
        cout << "nullptr" << endl;
    }
    
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
    newProduct->showInfo();
}

