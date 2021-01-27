//Абстрактная фабрика — это порождающий паттерн проектирования, который позволяет создавать семейства связанных объектов, не привязываясь к конкретным классам создаваемых объектов.

//Например стоит задача создания элементов формы под различные операционные системы. Сначала объявляется класс, описывающий  продукцию одного типа, например элемент формы кнопка.
//Наследуясь от данного класса описываются элементы конкрутных продуктов, например кнопка под ОС Windows и OC Linux
//Аналогично создаются классы продукции относящиеся к данной же теме, но другого типа, например флажки выбора, виджеты, текстовые поля и т.п.

//Затем создается класс абстрактной фабрики, в которой объявляются методы для создания продукции разных типов. Например методы для создания кнопок и методы для создания флажков или текстовых полей
//Наследуемые классы фабрик реализуют создание объектов разного типа, находящихся в конкретной области, например методы создания кнопок, флажкой, текстовых полей, конкретно под ОС Windows.
//Аналогично создается класс для другой области, например кнопки, флажки и текстовые поля под ОС Linux.
//Затем создается класс клиента, который связывает требования клиента с работой фабрик, т.е. при вводе определенного типа области, формируется фабрика данной области и дальнейшая работа будет происходить с выбранной областью.
//Например, если известно, что работа происходит в области Т1, то создается объект фабрики первого типа и дальнейшая работа происходит с объектами типа1,
//например при выборе ОС Windows объект client создает внутри себя фабрику для работы с объектами из области Windows  и функция doStuff начинает работать именно с элементами формы из ОС Windows.

//Для добавления еще одной ОС необходимо создать новый класс, унаследованный от абстракнтой фабрики. В новом классе описать поведение новой области и добавить в функции init возможность выбора новой фабрики.
//При создании нового типа элементов, например добавление элемента Label, создаются классы продукции, абстрактный и конкретные. Далее в соответствующих фабриках добавляются методы вызова данных продуктов.
//Т.о. данный паттерн позволяет добавлять новые типы данных или новые области работы с данными просто, не нарушая логику приложения, весь написанный функционал остается корректным.


#pragma once
#include <iostream>
#include <memory>
namespace factory {
  //INTERFACES
  //Product interfaces
  struct ProductA{
    virtual void doStaffA() = 0;
    virtual ~ProductA();
  };

  struct ConcreteProductA1: ProductA{
    void doStaffA() override;
    ~ConcreteProductA1() override;
  };

  struct ConcreteProductA2: ProductA{
    void doStaffA() override;
    ~ConcreteProductA2() override;
  };


  struct ProductB{
    virtual void doStaffB() = 0;
    virtual ~ProductB();
  };

  struct ConcreteProductB1: ProductB{
    void doStaffB() override;
    ~ConcreteProductB1() override;
  };

  struct ConcreteProductB2: ProductB{
    void doStaffB() override;
    ~ConcreteProductB2() override;
  };

  //Factory interfaces
  struct AbstractFactory{
    virtual std::unique_ptr<ProductA> createProductA() = 0;
    virtual std::unique_ptr<ProductB> createProductB() = 0;
    virtual ~AbstractFactory();
  };

  struct AbstractFactory1:AbstractFactory{
    virtual std::unique_ptr<ProductA> createProductA() override;
    virtual std::unique_ptr<ProductB> createProductB() override;
    ~AbstractFactory1() override;
  };

  struct AbstractFactory2:AbstractFactory{
    virtual std::unique_ptr<ProductA> createProductA() override;
    virtual std::unique_ptr<ProductB> createProductB() override;
    ~AbstractFactory2() override;
  };

struct Client{
  Client(std::unique_ptr<AbstractFactory> f);
  void doStuff();
private:
  std::unique_ptr<AbstractFactory> factory ;
  std::unique_ptr< ProductA> prA ;
  std::unique_ptr< ProductB>prB ;

};

  //DEFINITIONS
  //Products definition
  ProductA::~ProductA (){}

  void ConcreteProductA1::doStaffA(){
    std::cout<<"Concrete Product A1"<<std::endl;
  }
  ConcreteProductA1::~ConcreteProductA1 (){}

  void ConcreteProductA2::doStaffA(){
    std::cout<<"Concrete Product A2"<<std::endl;
  }
  ConcreteProductA2::~ConcreteProductA2 (){}

  ProductB::~ProductB (){}

  void ConcreteProductB1::doStaffB(){
    std::cout<<"Concrete Product B1"<<std::endl;
  }
  ConcreteProductB1::~ConcreteProductB1 (){}

  void ConcreteProductB2::doStaffB(){
    std::cout<<"Concrete Product B2"<<std::endl;
  }
  ConcreteProductB2::~ConcreteProductB2 (){}

  //Factory def
  AbstractFactory::~AbstractFactory (){}

  std::unique_ptr<ProductA> AbstractFactory1::createProductA(){
    return std::make_unique<ConcreteProductA1>();
  }
  std::unique_ptr<ProductB> AbstractFactory1::createProductB(){
    return std::make_unique<ConcreteProductB1>();
  }
  AbstractFactory1::~AbstractFactory1 (){}

  std::unique_ptr<ProductA> AbstractFactory2::createProductA(){
    return std::make_unique<ConcreteProductA2>();
  }
  std::unique_ptr<ProductB> AbstractFactory2::createProductB(){
    return std::make_unique<ConcreteProductB2>();
  }
  AbstractFactory2::~AbstractFactory2 (){}

//Client def

  Client::Client(std::unique_ptr<AbstractFactory> f):factory(std::move(f)) {  }

  void Client::doStuff(){
    prA = factory->createProductA ();
    prB = factory->createProductB ();

    prA->doStaffA ();
    prB->doStaffB ();

  }

//INIT

  void init(std::string type){
    std::unique_ptr<Client> client ;
    if(type == "T1")
      client = std::make_unique<Client>(std::make_unique<AbstractFactory1>());
    if(type == "T2")
      client = std::make_unique<Client>(std::make_unique<AbstractFactory2>());

    client->doStuff ();

  }
}


