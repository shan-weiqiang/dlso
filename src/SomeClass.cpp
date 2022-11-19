#include "include/SomeClass.h"
#include <stdio.h>

SomeClass::SomeClass() { printf("default ctor\n"); }
SomeClass::SomeClass(const std::string &value) : name_{value} {
  age = 10;
  printf("%s:%u\n", name_.c_str(), age);
}
std::string SomeClass::get_name() const { return name_; }
int SomeClass::get_age() const { return age; }

SomeClass some{"hello"};

void __attribute__((constructor)) init() {
  // some variable can be accessed at this time, the address is known, but has
  // not been initialized so accessing memebers are all uninitialized value
  printf("%s:%u\n", some.get_name().c_str(), some.get_age());
}