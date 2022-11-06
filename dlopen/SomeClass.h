#include <chrono>
#include <iostream>
#include <thread>

class InnerClass
{
public:
  InnerClass() { std::cout << "InnerClass constructor called~" << this << std::endl; }
  ~InnerClass() { std::cout << "InnerClass destructor called~ " << this << std::endl; }
};
class SomeClass
{
public:
  InnerClass non_static;

public:
  SomeClass()
  {
    std::cout << "SomeClass constructor called~" << this << std::endl;
  }
  ~SomeClass() { std::cout << "SomeClass destructor called~" << this << std::endl; }
};
