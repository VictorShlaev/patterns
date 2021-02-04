#include "factoryMethod.hpp"
#include "factory.hpp"
#include "builder.hpp"
#include "prototype.hpp"
#include "singleton.hpp"
#include "adapter.hpp"
void start(){
  factoryMethod::init ("B");
  factory::init ("T1");
  builder::init("One","B");
  prototype::init();
  singleton::init();
  adapter::init();
}

int main()
{
  start ();
  return 0;
}
