/*
*
*Декоратор — это структурный паттерн проектирования, который позволяет динамически добавлять объектам новую функциональность, оборачивая их в полезные «обёртки».
*НАпример стоит задача отправки сообщения несколькими способами. Если унаследоваться от общего класса и реализовать конкретные способы оправки, то
*при потребности в отправке сообщения несколькими способами придется делать много классов для компоновки.
*Решением является использовать композицию вместо наследования, создать класс обертку, содержащую функции основного интерфейса и экземпляр базового класса,
*далее создаются конкретные декораторы, т.е. способы обработки, например метод отправки сообщения. Далее пользователь через декоратора вызывает функцию обработки
* и вызывается необходимая обработка обертки
*/

#pragma once

#include <iostream>
#include <memory>
using namespace std;
namespace wrapper {
  //interfaces
  //Компонент задаёт общий интерфейс оберток и оборачиваемых объектов
  struct Component{
    virtual void execute()=0;
    virtual ~Component();
  };

  //Конкретный компонент определяет класс оборачиваемых объектов. Он содержит какое-то базовое поведение,
  //которое потом изменяют декораторы.
  struct ConcreteComponent: Component{
    void execute() override;
    ~ConcreteComponent() override;
  };

  //Базовый декоратор хранит ссылку на вложенный объект-компонент.
  //Им может быть как конкретный компонент, так и один из конкретных декораторов.
  //Базовый декоратор делегирует все свои операции вложенному объекту.
  //Дополнительное поведение будет жить в конкретных декораторах.
  struct BaseDecorator: Component{
      BaseDecorator();
    virtual void execute() override;
    BaseDecorator(unique_ptr<Component> c);
    ~BaseDecorator() override;
protected:
    unique_ptr<Component> wrappee; //оборачиватель
  };
  //Конкретные декораторы — это различные вариации декораторов, которые содержат добавочное поведение. Оно выполняется до или после вызова аналогичного поведения обёрнутого объекта.
  struct ConcreteDecoratorA: public BaseDecorator{
      explicit ConcreteDecoratorA(unique_ptr<Component> c);
      void execute() override;
      ~ConcreteDecoratorA() override;
  };

  struct ConcreteDecoratorB: BaseDecorator{
   explicit ConcreteDecoratorB(unique_ptr<Component> c);
    void execute() override;
    ~ConcreteDecoratorB() override;
  };

  //defines
  Component::~Component()
  {
    cout<<"~Component"<<endl;
  }
  //concr comp
  void ConcreteComponent::execute()
  {
    cout<<"ConcreteComponent::execute"<<endl;
  }

  ConcreteComponent::~ConcreteComponent()
  {
    cout<<"~ConcreteComponent"<<endl;
  }
  //Base decorator
  inline BaseDecorator::BaseDecorator()
  {

  }

  void BaseDecorator::execute()
  {
    cout<<"BaseDecorator::execute"<<endl;

  }

  inline BaseDecorator::BaseDecorator(unique_ptr<Component> c)
  {
    wrappee = move(c);
  }

  inline BaseDecorator::~BaseDecorator()
  {
    cout<<"~BaseDecorator"<<endl;
  }
  //Concr decA
   ConcreteDecoratorA::ConcreteDecoratorA(unique_ptr<Component> c)
  {
      wrappee = move(c);
  }

  void ConcreteDecoratorA::execute()
  {
    cout<<"ConcreteDecoratorA::execute"<<endl;
    wrappee->execute();
  }

  inline ConcreteDecoratorA::~ConcreteDecoratorA()
  {
    cout<<"~ConcreteDecoratorA"<<endl;
  }

  //conc dec B
  inline ConcreteDecoratorB::ConcreteDecoratorB(unique_ptr<Component> c)
  {
      wrappee =move(c);
  }

  void ConcreteDecoratorB::execute()
  {
    cout<<"ConcreteDecoratorB::execute"<<endl;
    wrappee->execute();
  }

  inline ConcreteDecoratorB::~ConcreteDecoratorB()
  {
    cout<<"~ConcreteDecoratorB"<<endl;
  }

  //init
  void init(string type){
    cout<<"\nWRAPPER PATTERN"<<endl;
    auto worker = make_unique<ConcreteComponent> ();
    unique_ptr<BaseDecorator> bd ;

    if(type == "A"){
          bd = make_unique<ConcreteDecoratorA>(move(worker));
      }
    if(type=="B"){
        bd = make_unique<ConcreteDecoratorB>(move(worker));
      }
    bd->execute ();
  }

}
