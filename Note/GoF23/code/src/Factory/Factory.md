# 工厂模式(Factory)
**定义：** 定义一个创建产品对象的工厂接口，将产品对象的实际创建工作推迟到具体子工厂类当中，实现“创建与使用相分离”的特点。

与单例模式、原型模式、建造者模式同属于创建型设计模式。包含以下 3 种：
1. 简单工厂模式
2. 工厂方法模式
3. 抽象工厂模式
4. 提高封装性的工厂模式

## 1、简单工厂模式
``` mermaid
classDiagram
AbstractProduct <|.. ConcreteProductA : 实现
AbstractProduct <|.. ConcreteProductB : 实现
ConcreteProductA <.. SimpleFactory : Create
ConcreteProductB <.. SimpleFactory : Create
SimpleFactory <.. Client : producrType
AbstractProduct <.. Client

class AbstractProduct{
    <<interface>>
    +ShowName() string
}

class ConcreteProductA{
    +ShowName() string
}
class ConcreteProductB{
    +ShowName() string
}

class SimpleFactory{
    +AbstractProduct* CreateProduct(string type)
}

class Client{
    
}

```

### 简单工厂类模式结构
单流水线工厂，只能从规定的产品类型中选出要生产的产品，则工厂就只生产该类型的产品。如：我的工厂现在能生产可乐、咖啡和红酒，顾客需要选择生产的类型，那我就全流水线生产。
* 产品抽象类（Product）：工厂创建所有产品的基类，负责描述所有实例共有的公共接口。
* 具体产品类（ConcreteProduct）：简单工厂模式的创建目标。
* 简单工厂类（SimpleFactory）：简单工厂类模式核心组件，负责产品实例创建的所有逻辑，对外提供创建具体产品的方法。

#### 优点：
1. 免除客户端直接创建产品对象的职责，工厂和产品的职责区分明确。
2. 工厂类包含必要的逻辑判断，客户端传入产品类型，无需知道所创建具体产品的类名就可以创建哪一个产品的实例。
3. 也可以引入配置文件，在不修改客户端代码的情况下更换和添加新的具体产品类。

#### 缺点：
1. 简单工厂模式的工厂类单一，负责所有产品的创建，职责过重，一旦异常，整个系统将受影响。且工厂类代码会非常臃肿，违背高聚合原则。
2. 由于工厂类判断产生具体的产品实例，因此，每加一个新的具体产品类，都需要修改工厂类的逻辑代码，违反开闭原则。

#### 使用场景：
* 产品种类相对较少的情况，客户端只需要传入工厂类的参数，不需要关心如何创建对象的逻辑，可以很方便地创建所需产品。


## 2、工厂方法模式
一系列类型的工厂集团，但只支持品牌产品的定制化，一个工厂只能生产一种类型的具体产品。如：旗下有一个李宁牌工厂，但只能定制化生产韦德之道球鞋；华为牌工厂，但只能生产手机。

``` mermaid
classDiagram

AbstractProduct <|.. ConcreteProductA : 实现
AbstractProduct <|.. ConcreteProductB : 实现
class AbstractProduct{
    <<interface>>
    +ShowName() string
}
class ConcreteProductA{
    +ShowName() string
}
class ConcreteProductB{
    +ShowName() string
}

AbstractFactory <|.. ConcreteFactoryA : 实现
AbstractFactory <|.. ConcreteFactoryB : 实现
class AbstractFactory{
    <<interface>>
    +AbstractProduct* CreateProduct() 
}
class ConcreteFactoryA{
    +AbstractProduct* CreateProduct()
}
class ConcreteFactoryB{
    +AbstractProduct* CreateProduct()
}

ConcreteProductA <.. ConcreteFactoryA : create
ConcreteProductB <.. ConcreteFactoryB : create
AbstractFactory <.. Client
AbstractProduct <.. Client
class Client{
    
}

```

### 工厂方法模式结构
由抽象工厂、具体工厂、抽象产品和具体产品四个要素组成：
* 抽象工厂类（AbstractFactory）：提供创建产品的接口，client 通过它调用具体工厂的 CreateProduct 方法创建产品
* 具体工厂类（ConcreteFactory）：实现抽象工厂中的抽象方法，完成具体产品的创建。
* 抽象产品类（AbstractProduct）：定义了产品的规范，描述了产品的主要特性和功能。
* 具体产品（ConcreteProduct）：实现了抽象产品角色所定义的接口，由具体工厂来创建，它同具体工厂之间一一对应。

#### 优点：
1. 典型的解耦框架。高层模块只需要知道产品的抽象类，无须关心其他实现类，满足迪米特法则、依赖倒置原则和里氏替换原则。
2. 灵活性增强，对于新产品的创建，只需多写一个相应的工厂类。

#### 缺点：
1. 每新增一个产品，就需要增加一个对应的产品的具体工厂类。类的个数容易过多，增加复杂度
2. 每个工厂只对应一个产品，抽象产品只能生产一种产品，此弊端可使用抽象工厂模式解决。

#### 使用场景：
* 客户无需知道产品类型，只知道创建产品的工厂就行。传说中的品牌效应？


## 3、抽象工厂模式
综合性工厂，能为一个品牌方提供全套服务。如：华为牌工厂支持生产手机、电脑和耳机等等，而不是仅限于手机了。
``` mermaid
classDiagram

AbstractProductA <|.. ConcreteProductA : 实现
class AbstractProductA{
    <<interface>>
    +ShowName() string
}
class ConcreteProductA{
    +ShowName() string
}

AbstractProductB <|.. ConcreteProductB : 实现
class AbstractProductB{
    <<interface>>
    +ShowName() string
}
class ConcreteProductB{
    +ShowName() string
}

AbstractFactory <|.. ConcreteFactory : 实现
class AbstractFactory{
    <<interface>>
    +AbstractProductA* CreateProductA() 
    +AbstractProductB* CreateProductB() 
}
class ConcreteFactory{
    +AbstractProductA* CreateProductA() 
    +AbstractProductB* CreateProductB() 
}

ConcreteProductA <.. ConcreteFactory : create
ConcreteProductB <.. ConcreteFactory : create

AbstractFactory <.. Client
AbstractProductA <.. Client
AbstractProductB <.. Client
class Client{
    
}

```

### 抽象工厂模式结构
是一种为访问类提供一个创建一组相关或相互依赖对象的接口，且访问类无须指定所要产品的具体类就能得到同族的不同等级的产品的模式结构。

由抽象工厂、具体工厂、抽象产品和具体产品四个要素组成：
* 抽象工厂类（AbstractFactory）：提供创建产品的接口，包含多个创建产品的方法，可以创建多个不同等级的产品。
* 具体工厂类（ConcreteFactory）：实现抽象工厂中的抽象方法，完成具体产品的创建。
* 抽象产品类（AbstractProduct）：定义了产品的规范，描述了产品的主要特性和功能。抽象工厂模式有多个抽象产品。
* 具体产品（ConcreteProduct）：实现了抽象产品角色所定义的接口，由具体工厂来创建。同具体工厂之间是多对一的关系。

#### 优点：
1. 在类的内部对产品族中相关联的多等级产品共同管理，而不必专门引入多个新的类来进行管理。
2. 当需要产品族时，抽象工厂可以保证客户端始终只使用同一个产品的产品组。
3. 抽象工厂增强了程序的可扩展性，当增加一个新的产品族时，不需要修改原代码，满足开闭原则。

#### 缺点：
1. 当产品族中需要增加一个新的产品时，需要增加一个对应的产品的具体工厂类。

#### 使用场景：
* 系统中有多个产品族，每个具体工厂创建同一族但属于不同等级结构的产品。
* 系统一次只可能消费其中某一族产品，即同族的产品一起使用。

### 总结
* 简单工厂模式，需要去修改工厂类，这违背了开闭法则。
* 工厂方式模式和抽象工厂模式，都需要增加一个对应的产品的具体工厂类，这就会增大了代码的编写量。



[改善版的方法：https://zhuanlan.zhihu.com/p/83537599](https://zhuanlan.zhihu.com/p/83537599)



``` mermaid
classDiagram
AbstractFactory ~class AbstractProduct_t~ <|.. ConcretFactory~class AbstractProduct_t, class ConcreteProduct~ : 实现

class AbstractFactory ~class AbstractProduct_t~{
	<<interface>>
	+AbstractProduct_t* CreateProduct() 
}

class ConcretFactory ~class AbstractProduct_t, class ConcreteProduct~{
	+AbstractProduct_t* CreateProduct()
}


AbstractProductA <|.. ConcreteProductA : 实现
AbstractProductB <|.. ConcreteProductB : 实现
ConcreteProductA <.. ConcretFactory~class AbstractProduct_t, class ConcreteProduct~ : create
ConcreteProductB <.. ConcretFactory~class AbstractProduct_t, class ConcreteProduct~ : create

class AbstractProductA{
	 <<interface>>
    +ShowName() string
}
class AbstractProductB{
	<<interface>>
    +ShowName() string
}

class ConcreteProductA{
    +ShowName() string
}
class ConcreteProductB{
    +ShowName() string
}
ConcretFactory~class AbstractProduct, class ConcreteProduct~  <.. client
class client{
	
}

```

