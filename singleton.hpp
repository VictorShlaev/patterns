/*
 *Одиночка — это порождающий паттерн проектирования, который гарантирует, что у класса есть только один экземпляр, и предоставляет к нему глобальную точку доступа.
 *Например при работе с базой данных класс БД создается в одном экзмепляре. Для этого конструктор объявляется приватным, создается переменная типа Одиночка, память под которую выделяется однажды.
 *Дальнейшая работа происходит с использованием функции, которая передает указатель на объект одиночки. Т.о. все объекты данного класса на самом деле работают с одним пространством.
*/

#pragma once
#include <iostream>
#include <memory>
namespace singleton {
//interface
struct SingletonClass{
    static SingletonClass* getInstance();
    void printObjCnt();
private:
    SingletonClass() ;
    static SingletonClass *instance;
    static int objCnt;
};
//defines
SingletonClass* SingletonClass::instance = nullptr;
int SingletonClass::objCnt = 0;

inline SingletonClass::SingletonClass(){instance = nullptr;}
inline SingletonClass *SingletonClass::getInstance()
{
    if(instance == nullptr){
        std::cout<<"First creating"<<std::endl;
        instance = new SingletonClass();
    }else{
        std::cout<<"already created"<<std::endl;
    }
    ++objCnt;
    return instance;
}

inline void SingletonClass::printObjCnt()
{
    std::cout<<"obj cnt: "<<objCnt<<std::endl;
}


//init fun
void init(){
    std::cout<<"SINGLETON PATTERN"<<std::endl;
    auto singlA = SingletonClass::getInstance();
    singlA->printObjCnt();
    SingletonClass* singlB = SingletonClass::getInstance();
    singlB->printObjCnt();
    SingletonClass* singlC = SingletonClass::getInstance();
    singlC->printObjCnt();


}
}
