#include "Foo.hpp"

#include <iostream>

Foo::Foo()
{
  std::cout << "Created Foo" << std::endl;
}

void Foo::print_stuff()
{
  std::cout << "Print stuff" << std::endl;
}
