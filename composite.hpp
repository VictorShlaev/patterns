/*
*Компоновщик — это структурный паттерн проектирования, который позволяет сгруппировать множество объектов в древовидную структуру, а затем работать с ней так, как будто это единичный объект.
*Условно, если есть сложный объект, подобие матрешки или например, коробка с коробками, то нет необходимости вызывать для каждой коробки метод по отдельности.
*Предлагается объедетить их в форму дерева, в которой есть сложные и простые объекты, простые объекты, это листья, которые непосредственно вызывают методы, т.е. конкретную работу выполняют,
*а сложные объекты при вызове метода просто вызывают данный метод у потомков, если потомки листья, то начинается производиться конкретное действие, иначе команда вызова передается ниже до выполнения действия.
*
*
*/

#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

namespace composite {
//interfaces

//Компонент определяет общий интерфейс для простых и составных компонентов дерева
struct Component{

    virtual void execute();
    virtual ~Component() ;
};

//Лист - простой компонент дерева без ответвлений
//т.к. больше некому передавать управление, то в основном весь полезный код в листьях
struct Leaf: Component{
    void execute () override;
    ~Leaf() override;
};

//Лист - простой компонент дерева без ответвлений
//Eще один лист
struct LeafTwo: Component{
    void execute () override;
    ~LeafTwo() override;
};

//Контейнер - составной компонент дерева
//Он содержит набор дочерних компонентов, но ничего не знает про их тип.
//Это могут быть как листья, так и другие контейнеры, но это не проблема, т.к. вызывая метод execute у детей
//вызывается по цепочке методы до тех пор, пока не будут достигнуты листья.
struct Composite: Component{
    void execute() override;
    void add(unique_ptr<Component> c);
    ~Composite() override;

private:
    vector<unique_ptr<Component>> children;
};

//defines
void Component::execute()
{
    cout<<"Component::executed"<<endl;
}

Component::~Component()
{
    cout<<"~Component"<<endl;
}

void Leaf::execute()
{
    cout<<"Leaf::execute"<<endl;
}

inline Leaf::~Leaf()
{
    cout<<"~Leaf"<<endl;
}

void LeafTwo::execute()
{
    cout<<"LeafTwo::execute"<<endl;
}

inline LeafTwo::~LeafTwo()
{
    cout<<"~LeafTwo"<<endl;
}

void Composite::execute()
{
    cout<<"Composite execute"<<endl;
    //вызывается метод для всех детей, если это композит, то там аналогичная функция, для всех потомков
    for(const auto& child: children){
        child->execute ();
    }
}

inline void Composite::add(unique_ptr<Component> c)
{
    children.push_back (move(c));
}

inline Composite::~Composite()   {   }



//init
void init(){
    cout<<"\n COMPOSITE PATTERN"<<endl;
    vector<unique_ptr<Component>> vals;
    vals.push_back (make_unique<Leaf>());
    vals.push_back (make_unique<LeafTwo>());
    unique_ptr<Component> c1 = make_unique<Leaf> ();
    unique_ptr<Component> c2 = make_unique<LeafTwo> ();
    unique_ptr<Composite> composite = make_unique<Composite>();
    composite->add(move(c1));
    composite->add(move(c2));

    vals.push_back (move(composite));
    for(const auto& val: vals){
        val->execute ();
    }
}
}
