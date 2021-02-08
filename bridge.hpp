/*
*Мост — это структурный паттерн проектирования, который разделяет один или несколько классов на две отдельные иерархии — абстракцию и реализацию, позволяя изменять их независимо друг от друга.
*Например стоит задача написания классов геометрических фигур различных цветов. Одним из решений является создать конкретные фигуры и затем для этих фигур создать фигуры конкретного цвета.
*С добавлением фигуры или цвета придется создать либо один дополнительный либо количеством цветов классов.
*Класс фигур называется абстракцией, т.е. класс, с которым непосредственно работает пользователь,
*класс цветов называется реализацией.
*Предлагается разделить логику фигур и цветов на два класса и вместо наследования использовать композицию.
*Т.е. в классе абстракции (фигур) завести поле реализации (цвета) и, например, в конструктор передавать необходимую
*реализацию фигуры(необходимый класс цвета).
*Т.о. при добавлении новой фигуры или нового цвета достаточно будет создать один новый класс для новой сущности.
*
*
*/

#pragma once
#include <iostream>
#include <memory>
using namespace std;
namespace bridge {
//interfaces
//exam colors
struct Implementation {
    virtual void imp1();
    virtual ~Implementation();
};
//exam red color
struct ConcreteImplementation:Implementation{
    void imp1() override;
    ~ConcreteImplementation() override;
};

//exam blue color
struct ConcreteImplementationTwo:Implementation{
    void imp1() override;
    ~ConcreteImplementationTwo() override;
};

//exam shapes
struct Abstraction{
    virtual void abstr1() = 0;
    virtual void abstr2() = 0;
    virtual ~Abstraction();
protected:
    unique_ptr<Implementation> pImpl;
};

//exam triangle
struct ConcreteAbstraction:  Abstraction{
    ConcreteAbstraction(unique_ptr<Implementation> impl);
    void abstr1() override;
    void abstr2() override;
    ~ConcreteAbstraction() override;
};

//exam rectangle
struct ConcreteAbstractionTwo:  Abstraction{
    ConcreteAbstractionTwo(unique_ptr<Implementation> impl);
    void abstr1() override;
    void abstr2() override;
    ~ConcreteAbstractionTwo() override;
};

//defines

inline void Implementation::imp1()
{
    cout<<"Implementation::imp1"<<endl;
}

inline Implementation::~Implementation()
{
    cout<<"~Implementation"<<endl;
}

inline void ConcreteImplementation::imp1()
{
    cout<<"Concrete Implementation::imp1"<<endl;
}

inline ConcreteImplementation::~ConcreteImplementation()
{
    cout<<"~ConcreteImplementation"<<endl;
}

inline void ConcreteImplementationTwo::imp1()
{
    cout<<"ConcreteImplementatipnTwo::imp1"<<endl;
}

inline ConcreteImplementationTwo::~ConcreteImplementationTwo()
{
    cout<<"~ConcreteImplementationTwo"<<endl;
}

inline Abstraction::~Abstraction()
{
    cout<<"~Abstraction"<<endl;
}

inline ConcreteAbstraction::ConcreteAbstraction(unique_ptr<Implementation> impl)
{
    pImpl = move(impl);
}

inline void ConcreteAbstraction::abstr1()
{
    cout<<"ConcreteAbstraction::abstr1 "<<endl;
    pImpl->imp1();
}

inline void ConcreteAbstraction::abstr2()
{
    cout<<"ConcreteAbstraction::abstr2 "<<endl;
    pImpl->imp1();
}

inline ConcreteAbstraction::~ConcreteAbstraction()
{
    cout<<"~ConcreteAbstraction"<<endl;
}

inline ConcreteAbstractionTwo::ConcreteAbstractionTwo(unique_ptr<Implementation> impl)
{
    pImpl= move(impl);
}

inline void ConcreteAbstractionTwo::abstr1()
{
    cout<<"ConcreteAbstractionTwo::abstr1 "<<endl;
    pImpl->imp1();
}

inline void ConcreteAbstractionTwo::abstr2()
{
    cout<<"ConcreteAbstractionTwo::abstr2 "<<endl;
    pImpl->imp1();
}

inline ConcreteAbstractionTwo::~ConcreteAbstractionTwo()
{
    cout<<"~ConcreteAbstractionTwo"<<endl;
}
//init
void init(string abstrType, string ImplType){
    cout<<"BRIDGE PATTERN"<<endl;
    unique_ptr<Implementation> implem;
    unique_ptr<Abstraction> abstr;
    //exam red triangle
    if(abstrType == "aA" && ImplType == "iA"){
        implem = make_unique<ConcreteImplementation>();
        abstr = make_unique<ConcreteAbstraction>(move(implem));
    }
    //exam red rectangle
    if(abstrType == "aB" && ImplType == "iA"){
        implem = make_unique<ConcreteImplementation>();
        abstr = make_unique<ConcreteAbstractionTwo>(move(implem));

    }
    //
    //...
    //
    abstr->abstr1();
    abstr->abstr2();
}
}
