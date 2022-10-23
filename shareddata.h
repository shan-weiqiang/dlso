#include <chrono>
#include <iostream>
#include <thread>

class InnerClass {
public:
  int a = 0;
  InnerClass() { std::cout << "InnerClass constructor called~\n"; }
  ~InnerClass() { std::cout << "InnerClass destructor called~ \n"; }
};
class SomeClass {
public:
  /** static memeber constructor will be called after SomeClass constructor
   */
  static InnerClass inner;
  InnerClass non_static;

public:
  int a;
  SomeClass(const int &init) : a{init} {
    std::cout << "SomeClass constructor called, a == " << a << "\n";
  }
  ~SomeClass() { std::cout << "SomeClass destructor called~\n"; }
};
