#include "factoryMethod.hpp"
#include "factory.hpp"

void start(){
  factoryMethod::init ("B");
  factory::init ("T1");
}

int main()
{
  start ();
  return 0;
}
