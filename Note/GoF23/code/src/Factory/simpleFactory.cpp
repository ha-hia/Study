#include "simpleFactory.h"
using namespace std;
/*******************************产品相关****************************************/
AbstractProduct::AbstractProduct()
{
}
AbstractProduct::~AbstractProduct()
{
}

ConcreteProductA::ConcreteProductA() : m_productName("ProductA")
{
}
ConcreteProductA::~ConcreteProductA()
{
}
void ConcreteProductA::ShowName()
{
    cout << m_productName << endl;
}

ConcreteProductB::ConcreteProductB() : m_productName("ProductB")
{
}
ConcreteProductB::~ConcreteProductB()
{
}
void ConcreteProductB::ShowName()
{
    cout << m_productName << endl;
}
/***********************************************************************/

SimpleFactory::SimpleFactory()
{
}

SimpleFactory::~SimpleFactory()
{
}
AbstractProduct* SimpleFactory::CreateProduct(ProductType::TYPE productType)
{
    switch (productType)
    {
    case ProductType::TYPEA:
        return new ConcreteProductA;
        break;
    case ProductType::TYPEB:
        return new ConcreteProductB; 
        break;   
    default:
        return nullptr;
        break;
    }
}
/***********************************************************************/
void TestSimpleFactory()
{
    AbstractProduct* productA = SimpleFactory::CreateProduct(ProductType::TYPEA);
    productA->ShowName();
    delete productA;
    productA = nullptr;

    AbstractProduct* productB = SimpleFactory::CreateProduct(ProductType::TYPEB);
    productB->ShowName();
    delete productB;
    productB = nullptr;
}