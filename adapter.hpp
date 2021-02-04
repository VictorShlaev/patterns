/*
 *Адаптер — это структурный паттерн проектирования, который позволяет объектам с несовместимыми интерфейсами работать вместе
 *Например, проблема заключается в совместимости типов данных для печати. Т.е. хотелось бы распечатать или нарисовать с использованием
 *одной и той же функции вектор, только данные стороннего класса имеют другой тип, в сравнении с клиентским классом.
 *Для этого создается класс адаптер, который является наследником клиентского класса, с полем типа стороннего класса.
 *Далее переопределяется нужный метод, таким образом, что данные приводятся в удобный для клиентской функции формат.
 *В результате появляется возможность работать со сторонним классом через интерфейс клиентского класса через адаптер.
 *
 *Другой пример, когда требуется использовать клиентский класс в качестве регистратора, т.е. класса, который записывает данные на диск.
 *Пусть функция записи в файл принимает действительный вектор. Для подобных типов можно создать шаблонный метод, но если понадобится записать
 *комплексный вектор, то функция не подойдет уже. Для решения данной проблемы можно создать еще один шаблонный метод.
 *С появлением нестандартных типов потребуется создание множества методов.
 *Другим решением является создание класса адаптера - наследника клиенского класса, конструктор которого принимает указатели на сторонние классы, которые требуется обработать.
 *Далее в переопределении метода записи комплексный вектор обрабатывается необходимым образом и происходит регистрация.
 *Работать же можно с использованием интерфейса клиентского класса.
*/

#pragma once
#include <iostream>
#include <complex>
#include <vector>
#include <memory>
using namespace std;
namespace adapter {
//interfaces
struct ClientInterface{
    virtual void print(vector<double>& arr);
    virtual ~ClientInterface();
};


struct ServiceInterface{
    vector<complex<double> > servPrint(vector<double> &arr);
    ~ServiceInterface();
};


struct Adapter: ClientInterface{
    Adapter(unique_ptr<ServiceInterface> _service);
    void print(vector<double>& arr) override;
    ~Adapter();

private:
    unique_ptr<ServiceInterface> service;
};


//defines
inline void ClientInterface::print(vector<double> &arr)
{
    for(const auto &val: arr)
        cout<<val<<" ";
    cout<<endl;
}
inline ClientInterface::~ClientInterface(){}


inline vector<complex<double>>  ServiceInterface::servPrint(vector<double > &arr)
{
    vector<complex<double>> res;
    for(const auto& val: arr)
        res.push_back({val,-1.});
    return res;
}
inline ServiceInterface::~ServiceInterface(){}


inline Adapter::Adapter(unique_ptr<ServiceInterface> _service):service(std::move(_service)){}
inline void Adapter::print(vector<double> &arr)
{
    vector<complex<double>> res = service->servPrint(arr);
    for(const auto& val: res){
        cout<<abs(val)<<" : "<<arg(val);
        cout<<endl;
    }
    cout<<endl;
}
inline Adapter::~Adapter(){}

//init
void init(){
    cout<<"ADAPTER PATTERN"<<endl;
    vector<double> objVec {1,-10,100,14,15,4.5,-3.14,-222222.10001,0.2341};
    vector<unique_ptr<ClientInterface>> obj;
    auto client = make_unique<ClientInterface>();
    auto serv = make_unique<ServiceInterface>();
    auto adapter = make_unique<Adapter>(move(serv));
    obj.push_back(move(client));
    obj.push_back(move(adapter));

    for(const auto& ptr: obj){
        ptr->print(objVec);
    }
}
}
