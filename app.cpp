#include "include/SomeClass.h"
#include <dlfcn.h>
#include <iostream>

int main() {
  auto handle = dlopen("build/libsome.so", RTLD_LOCAL | RTLD_NOW);
  if (!handle) {
    printf("%s", dlerror());
  }
}
