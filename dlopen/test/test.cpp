#include "greet/inc/Greet.h"
#include <iostream>
#include <stdio.h>
using namespace std;

extern "C" {
int a = 9;
Greet g;
void func_without_definition(double a);
}
// { printf("hello~\n"); }
struct OnlyDeclare {
  void som_func();
};
OnlyDeclare some;

void __attribute__((constructor)) f();
void __attribute__((constructor)) f() {
  printf("<<< now libtest-->((constructor)) is called~ <<<\n");
  printf("global a of libtest: %d\n", a);
  printf("address of a: %p\n", &a);
  printf("address of g of libtest: %p\n", &g);
  printf("<<< end of libtest-->((constructor)) <<<\n");
  // func_without_definition(23);
}
