
#include "AbstractFactory.h"
namespace Abstract {

    AbstractProductA* ConcreteFactoryNike::CreateProductA()
    {
        return new ProductA;
    }

    AbstractProductB* ConcreteFactoryNike::CreateProductB()
    {
        return new ProductB;
    }

    void TestAbstractFactory()
    {
        AbstractFactory* factory = new ConcreteFactoryNike;
        AbstractProductA* A = factory->CreateProductA();
        AbstractProductB* B = factory->CreateProductB();

        A->ShowName();
        B->ShowName();
    }
}