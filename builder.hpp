
//Строитель — это порождающий паттерн проектирования, который позволяет создавать сложные объекты пошагово.
//Строитель даёт возможность использовать один и тот же код строительства для получения разных представлений объектов
//Класс строителя позволяет создать объекты различной конфигурации, для этого в классе создаются методы строительства конкретных объектов.
//Если характеристики отличаются, то создаются конкретные строители.
//Например, задача состоит в написании класса для строительства дома. Дома бывают разные и для того, чтобы не плодить конструкторы и классы
//наследники, создается один класс строитель дома, в котором находятся поля и методы для всех вариантов домов. КОгда же необходимо создать конкретный
//дом, то вызываются необходимые поля и методы для строительства дома. Для упрощения строительства заводят класс директо, который конфигурирует строительство под нужды,
//т.е. пользователь директору указывает какой дом нужен, а директор вызывает необходимые методы у строителя, предоставляет интерфейс для работы с создаваемым объектом.

#pragma once
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
namespace builder {
//interfaces
struct Builder{
    virtual void buildStepA() = 0;
    virtual void buildStepB() = 0;
    virtual void buildStepC() = 0;
    virtual ~Builder();
};

struct ProductOne{
    ProductOne();
};


struct ConcreteBuilderOne:Builder{
    void buildStepA() override;
    void buildStepB() override;
    void buildStepC() override;
    std::unique_ptr<ProductOne> createProduct();
    //    ProductOne* createProduct();
    ~ConcreteBuilderOne() override;
private:
    std::unique_ptr<ProductOne> product;
};

struct ProductTwo{
    ProductTwo();
};
struct ConcreteBuilderTwo:Builder{
    void buildStepA() override;
    void buildStepB() override;
    void buildStepC() override;
    std::unique_ptr<ProductTwo> createProduct();
    ~ConcreteBuilderTwo() override;
private:
    std::unique_ptr<ProductTwo> product;
};

//Director
struct Director{
    Director();
    Director(std::unique_ptr<Builder> _builder);
    void changeBuilde(std::unique_ptr<Builder> _builder);
    void buildProduct(std::string type);
    ~Director();
private:
    std::unique_ptr<Builder> builder;
};



//defines

Builder::~Builder(){}

void ConcreteBuilderOne::buildStepA(){
    cout<<"ConcreteBuilderOne::buildStepA"<<endl;
}

void ConcreteBuilderOne::buildStepB(){
    cout<<"ConcreteBuilderOne::buildStepB"<<endl;
}
void ConcreteBuilderOne::buildStepC(){
    product = createProduct();
    cout<<"ConcreteBuilderOne::buildStepC"<<endl;
}
std::unique_ptr<ProductOne> ConcreteBuilderOne::createProduct(){
    return std::make_unique<ProductOne>();
}
ConcreteBuilderOne::~ConcreteBuilderOne(){}

void ConcreteBuilderTwo::buildStepA(){
    cout<<"ConcreteBuilderTwo::buildStepA"<<endl;
}

void ConcreteBuilderTwo::buildStepB(){
    cout<<"ConcreteBuilderTWo::buildStepB"<<endl;
}
void ConcreteBuilderTwo::buildStepC(){
    product = createProduct();
    cout<<"ConcreteBuilderTwo::buildStepC"<<endl;
}
std::unique_ptr<ProductTwo> ConcreteBuilderTwo::createProduct(){
    return std::make_unique< ProductTwo>();
}
ConcreteBuilderTwo::~ConcreteBuilderTwo(){}


Director::Director(){}
Director::Director(std::unique_ptr<Builder> _builder):builder(std::move(_builder)){}
void Director::changeBuilde(std::unique_ptr<Builder> _builder){
    builder = std::move(_builder);
}
Director::~Director(){}

void Director::buildProduct(std::string type){
    if(type == "A")
        builder->buildStepA();
    else{
        builder->buildStepB();
        builder->buildStepC();
    }
}


ProductOne::ProductOne(){
    cout<<"ProductOne Created"<<endl;
}

ProductTwo::ProductTwo(){
    cout<<"ProductOne Created"<<endl;
}
//init
void init(std::string typeBuilder , std::string typeProd){
    cout<<"BUILDER PATTERN"<<endl;
    std::unique_ptr<Builder> builder;
    if(typeBuilder == "One")
        builder = std::make_unique <ConcreteBuilderOne>();
    else
        builder = std::make_unique<ConcreteBuilderTwo>();
    auto director = std::make_unique<Director>(std::move(builder));
    director->buildProduct(typeProd);

}
}
