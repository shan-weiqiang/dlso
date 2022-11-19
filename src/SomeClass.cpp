#include "include/SomeClass.h"
#include <iostream>

SomeClass::SomeClass(){};
SomeClass::SomeClass(const std::string &value) : name_{value} { age = 10; }
std::string SomeClass::get_name() { return name_; }


void anon_func();

void some_func() { anon_func(); }
