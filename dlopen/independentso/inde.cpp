#include "greet/inc/Greet.h"
#include <stdio.h>

Greet g;
__attribute__((constructor)) void func() {
  std::cout << "address of g in indepso: " << &g << '\n';
}
