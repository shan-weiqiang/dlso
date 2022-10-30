#include "greet/inc/Greet.h"
#include "sample.h"
#include <stdio.h>
// SampleStruct ex_sample;
Greet g;
__attribute__((constructor)) void func() {
  printf("address of g indepso: %p\n", &g);
}
