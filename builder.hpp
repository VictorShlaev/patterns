#pragma once

#include <iostream>
#include <string>
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

ProductOne::ProductOne(){
    cout<<"ProductOne Created"<<endl;
}
struct ConcreteBuilderOne:Builder{
    void buildStepA() override;
    void buildStepB() override;
    void buildStepC() override;
    ProductOne* createProduct();
    ~ConcreteBuilderOne() override;
private:
    ProductOne* product;
};


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
ProductOne* ConcreteBuilderOne::createProduct(){
    return new ProductOne;
}

ConcreteBuilderOne::~ConcreteBuilderOne(){delete product;}
struct ProductTwo{
    ProductTwo();
};

ProductTwo::ProductTwo(){
    cout<<"ProductOne Created"<<endl;
}
struct ConcreteBuilderTwo:Builder{
    void buildStepA() override;
    void buildStepB() override;
    void buildStepC() override;
    ProductTwo* createProduct();
    ~ConcreteBuilderTwo() override;
private:
    ProductTwo* product;
};


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
ProductTwo* ConcreteBuilderTwo::createProduct(){
    return new ProductTwo();
}

ConcreteBuilderTwo::~ConcreteBuilderTwo(){ delete product;}

//Director
struct Director{
    Director();
    Director(Builder* _builder);
    void changeBuilde(Builder* _builder);
    void buildProduct(std::string type);
    ~Director();
private:
    Builder* builder;
};
Director::Director(){}
Director::Director(Builder* _builder):builder(_builder){}
void Director::changeBuilde(Builder *_builder){
    delete  builder;
    builder = _builder;
}

void Director::buildProduct(std::string type){
    if(type == "A")
        builder->buildStepA();
    else{
        builder->buildStepB();
        builder->buildStepC();
    }
}

Director::~Director(){delete builder;}

//defines
//defines builder class
Builder::~Builder(){}


//init
void init(std::string typeBuilder , std::string typeProd){
    Builder* builder = nullptr;
    if(typeBuilder == "One")
        builder = new ConcreteBuilderOne();
    else
        builder = new ConcreteBuilderTwo();

    Director* director = new Director(builder);
    director->buildProduct(typeProd);
    delete director;
    delete builder;
}
}
