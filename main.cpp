#include "factoryMethod.hpp"
#include "factory.hpp"
#include "builder.hpp"

void start(){
  factoryMethod::init ("B");
  factory::init ("T1");
  builder::init("One","B");
}

int main()
{
  start ();
  return 0;
}
