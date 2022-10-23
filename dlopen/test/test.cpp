#include <iostream>
using namespace std;
#include "greet/inc/Greet.h"
#include <stdio.h>

extern "C" {
int a = 9;
Greet g;
}
void __attribute__((constructor)) f();
void __attribute__((constructor)) f() {
  printf("<<< now libtest-->((constructor)) is called~ <<<\n");
  printf("global a of libtest: %d\n", a);
  printf("address of a: %p\n", &a);
  printf("address of global g of libtest: %p\n", &g);
  printf("<<< end of libtest-->((constructor)) <<<\n");
}
