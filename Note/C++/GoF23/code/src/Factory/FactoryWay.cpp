#include "FactoryWay.h"
#include <memory>
using namespace std;

/***********************工厂***************************************/
AbstractFactory::AbstractFactory(/* args */)
{
}
AbstractFactory::~AbstractFactory()
{
}
/*********************** A 工厂*************************************/
ConcreteFactoryA::ConcreteFactoryA(/* args */)
{
}
ConcreteFactoryA::~ConcreteFactoryA()
{
}

AbstractProduct* ConcreteFactoryA::CreateProduct()
{
    return new ConcreteProductA;
}

/*********************** A 工厂*************************************/
AbstractProduct* ConcreteFactoryB::CreateProduct()
{
    return new ConcreteProductB;
}

void TestFactoryWay()
{
    shared_ptr<AbstractFactory> factoryA( new ConcreteFactoryA );    
    
    //AbstractProduct* A = factoryA->CreateProduct();
    //shared_ptr<AbstractProduct> proA = A;
    //shared_ptr<AbstractProduct> proA = make_shared<AbstractProduct> ( factoryA->CreateProduct() );
    shared_ptr<AbstractProduct> proA( factoryA->CreateProduct() );
    proA->ShowName();

    shared_ptr<AbstractFactory> factoryB( new ConcreteFactoryB );   
    shared_ptr<AbstractProduct> proB( factoryB->CreateProduct() );
    proB->ShowName(); 
}