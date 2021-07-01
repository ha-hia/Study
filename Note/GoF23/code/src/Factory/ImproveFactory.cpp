#include "ImproveFactory.h"
#include <memory>
using std::shared_ptr;

namespace ImproveFactory{
    void TestImproveFactory()
    {
        
        ConcreteFactory<AbstractProductA, ProductA> factoryA;
        shared_ptr< AbstractProductA > A( factoryA.CreateProduct() );
        A->ShowName();

        ConcreteFactory<AbstractProductB, ProductB> factoryB;
        shared_ptr< AbstractProductB > B( factoryB.CreateProduct() );
        B->ShowName();
    }

}
