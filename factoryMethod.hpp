#pragma once
#include <iostream>
#include <memory>
namespace factoryMethod{
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

  // //creator interface
  struct Creator
  {
    virtual Product* createProduct() = 0;
    virtual ~Creator();
  };


  struct ConcreteCreatorA:Creator
  {
    Product* createProduct() override;
    ~ConcreteCreatorA() override;
  };

  struct ConcreteCreatorB: Creator
  {
    Product* createProduct() override;
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

  Product* ConcreteCreatorA::createProduct() {
    return new ConcreteProdA();
  }
  ConcreteCreatorA::~ConcreteCreatorA(){}

  Product* ConcreteCreatorB::createProduct() {
    return new ConcreteProdB();
  }
  ConcreteCreatorB::~ConcreteCreatorB (){}
     //INIT FUN
      void init(std::string type){
        std::unique_ptr<Creator> creator;

//        Creator* creator = nullptr;
        if(type == "A")
          creator  =  std::make_unique<ConcreteCreatorA>();
        if(type == "B")
          creator  =  std::make_unique<ConcreteCreatorB>();

        Product* product  = creator->createProduct ();
        product->doStuff();

        delete  product;
      }
}
