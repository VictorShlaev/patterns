#include "factoryMethod.hpp"
#include "factory.hpp"

void start(){
  factoryMethod::init ("B");
  factory::init ("T2");
}

int main()
{
  start ();
  return 0;
}
