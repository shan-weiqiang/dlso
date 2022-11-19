#include "include/SomeClass.h"
#include <iostream>

int main() {
  SomeClass myclass{"Shan Weiqiang"};
  std::cout << myclass.get_name() << std::endl;
}
