/*
 *Прототип — это порождающий паттерн проектирования, который позволяет копировать объекты, не вдаваясь в подробности их реализации.
 *Прототип — это порождающий паттерн проектирования, который позволяет копировать объекты, не вдаваясь в подробности их реализации.
 *Паттерн Прототип поручает создание копий самим копируемым объектам. Он вводит общий интерфейс для всех объектов, поддерживающих клонирование.
 *Это позволяет копировать объекты, не привязываясь к их конкретным классам. Обычно такой интерфейс имеет всего один метод clone.
 *Реализация этого метода в разных классах очень схожа. Метод создаёт новый объект текущего класса и копирует в него значения всех полей собственного объекта. Так получится скопировать даже приватные поля.
 *Суть паттерна в том, что метод клонирования находится в классе клонируемого объекта, что позволяет копировать значения приватных полей
 *Создается базовый класс с конструктором копирования и  абстрактным методом клонирования, в конкретных классах наследниках переопределяется данный метод
 *и создаются соответствующие конструкторы.
 *В методе копирования создается объект текущего типа с переданным указателем this в конструктор копирования.
 *
 */



#pragma once
#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;


namespace prototype {
//interfaces
struct Prototype{
    Prototype();
    Prototype(Prototype* prototype);
    virtual unique_ptr<Prototype> clone() = 0;
    virtual void printFields();
    virtual ~Prototype();
    int fieldI;
    double fieldD;
};

struct ConcretePrototypeA:  virtual Prototype{
    ConcretePrototypeA();
    ConcretePrototypeA(ConcretePrototypeA* prototype);
    unique_ptr<Prototype> clone() override;
    void printFields() override;
    ~ConcretePrototypeA() override;
    int fieldIA;
};

struct ConcretePrototypeB: virtual Prototype{
    ConcretePrototypeB();
    ConcretePrototypeB(ConcretePrototypeB* prototype);
    unique_ptr<Prototype> clone() override;
    void printFields() override;
    ~ConcretePrototypeB() override;
    int fieldIB;
};



//defines
inline Prototype::Prototype(){}
inline Prototype::Prototype(Prototype *prototype):fieldI(prototype->fieldI), fieldD(prototype->fieldD){}
inline void Prototype::printFields()
{
    cout<<"super fields: "<<fieldI<<" "<<fieldD<<endl;
}
inline Prototype::~Prototype(){}


inline ConcretePrototypeA::ConcretePrototypeA(){}
inline ConcretePrototypeA::ConcretePrototypeA(ConcretePrototypeA *prototype):Prototype(prototype), fieldIA(prototype->fieldIA){}
inline unique_ptr<Prototype> ConcretePrototypeA::clone()
{
    return make_unique<ConcretePrototypeA>(this);
}
inline void ConcretePrototypeA::printFields()
{
    Prototype::printFields();
    cout<<"ConcretePrototypeA fields: "<<fieldIA<<endl;
}
inline ConcretePrototypeA::~ConcretePrototypeA(){}


inline ConcretePrototypeB::ConcretePrototypeB(){}
inline ConcretePrototypeB::ConcretePrototypeB(ConcretePrototypeB *prototype):Prototype(prototype), fieldIB(prototype->fieldIB){}
inline unique_ptr<Prototype> ConcretePrototypeB::clone()
{
    return make_unique<ConcretePrototypeB>(this);
}
inline void ConcretePrototypeB::printFields()
{
    Prototype::printFields();
    cout<<"ConcretePrototypeB fields: "<<fieldIB<<endl;
}
inline ConcretePrototypeB::~ConcretePrototypeB(){}

//init fun
void init(){
    std::cout<<"PROTOTYPE PATTERN"<<std::endl;
    vector<unique_ptr<Prototype>> elements;//вектор элементов продукции
    auto protA = make_unique<ConcretePrototypeA>();//объект конкретного продукта
    //заполнение полей
    protA->fieldI = 10;
    protA->fieldD = -3.14;
    protA->fieldIA = -10;
    //создание клона и запись в другой объект
    unique_ptr<Prototype> protCloneA = protA->clone();
    //помещение клона и оригинала в вектор
    elements.push_back(move(protA));
    elements.push_back(move(protCloneA));
    //создание объекта типа Б
    auto protB = make_unique<ConcretePrototypeB>();
    //заполнение полей
    protB->fieldI = 12;
    protB->fieldD = 3.1415;
    protB->fieldIB = -44;
    //помещение в вектор клона и оригинала соответственно
    elements.push_back(protB->clone());
    elements.push_back(move(protB));
    //вызов функции у всех объектов вектора для сравнения полей
    for(auto &el: elements){
        el->printFields();
    }
}

}
