
//Фабричный метод — это порождающий паттерн проектирования, который определяет общий интерфейс для создания объектов в суперклассе, позволяя подклассам изменять тип создаваемых объектов.
//Данный паттерн позволяет создавать объекты нужного типа, расширять функционал приложения без нарушения логики ранее написанного ПО.
//Например для создания оконного приложения  в различных системах необходимо реализовать стилизацию под определенную ОС.
//Для этого с использованием фабричного метода создается сначала интерфейс продукта, например окно приложения. Далее наследуясь от данного интерфейса реализуются конкретные продукты, например окно под Windows или под Linux
//Затем создается класс создателя, класс фабрики, у которого объявляется метод создать продукт (создать окно приложения) . Затем наследуясь от класса создателя, создаются классы конкретных создателей или конкретных фабрик. Например класс для создания окна под Windows
//или класс для создания окна под Linux
//Затем можно создать функцию для общения с пользователем. В зависимости от вводимых параметров выделяется память под определенную фабрику. Работа с созданием продукта происходит независимо от выбранной фабрики. Таким образом при добавлении еще одной ОС
//достаточно унаследовать класс новой ОС от класса Продукции, унаследовать новый класс создателя от класса Creator  и в функции инициализации добавить пункт выбора под новую ОС. Старый код остается корректным.

#pragma once
#include <iostream>
#include <memory>
namespace factoryMethod{
  //interfaces
  //common product interface
  struct  Product
  {
    virtual void doStuff() = 0;
    virtual ~Product();
  };

  //product A interface
  struct  ConcreteProdA: Product
  {
    void doStuff() override;
    ~ConcreteProdA() override;
  };

  //product B interface
  struct  ConcreteProdB: Product
  {
    void doStuff() override;
    ~ConcreteProdB() override;
  };

   //creator interface
  struct Creator
  {
    virtual std::unique_ptr<Product> createProduct() = 0;
    virtual ~Creator();
  };

  struct ConcreteCreatorA:Creator
  {
    std::unique_ptr<Product>createProduct() override;
    ~ConcreteCreatorA() override;
  };

  struct ConcreteCreatorB: Creator
  {
    std::unique_ptr<Product> createProduct() override;
    ~ConcreteCreatorB() override;
  };

  //METHODS DEFINITION
  //Product
  Product::~Product (){}

  void ConcreteProdA::doStuff() {
    std::cout<<"Product A"<<std::endl;
  }
  ConcreteProdA::~ConcreteProdA (){}

  void ConcreteProdB::doStuff() {
    std::cout<<"Product B"<<std::endl;
  }
  ConcreteProdB::~ConcreteProdB(){}
  //Creator
  Creator::~Creator (){}

  std::unique_ptr<Product> ConcreteCreatorA::createProduct() {
    return std::make_unique<ConcreteProdA>();
  }
  ConcreteCreatorA::~ConcreteCreatorA(){}

  std::unique_ptr<Product> ConcreteCreatorB::createProduct() {
    return std::make_unique<ConcreteProdB>();
  }
  ConcreteCreatorB::~ConcreteCreatorB (){}
     //INIT FUN
      void init(std::string type){

        std::unique_ptr<Creator> creator;
        if(type == "A")
          creator  =  std::make_unique<ConcreteCreatorA>();
        if(type == "B")
          creator  =  std::make_unique<ConcreteCreatorB>();
        std::unique_ptr<Product> product  = creator->createProduct();
        product->doStuff();
      }
}
