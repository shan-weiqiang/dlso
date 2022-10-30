#include "halfso/Half.h"
#include <dlfcn.h>
#include <iostream>

/** @attention: must use printf, instead of std::cout, since this funtions will
 * be called by shared libs initialization, std::cout will cause segmentation
 * fault.
 */
Half::Half() { printf("Half ctor in main called~\n"); }
Half::~Half() { printf("Half dtor main called~\n"); }

void Half::half_func() { printf("Half::half_func() in main called~\n"); }
extern int a;
int main() {
  /** @attention: a must be used to be in the symbol table and to link outside,
   * otherwise, a is equial to non-exist.
   */
  printf("address of a:%p\n", &a);
  /** @brief: following experiment shows that dlopened shared libs do NOT shared
   * symbols!!
   */
  std::cout << "<<< now start loading libdefinition.so~ <<<\n";
  auto handle = dlopen(
      "/home/osboxes/playground/dlso/dlso/build/dlopen/halfso/libdefinition.so",
      RTLD_NOW);
  if (!handle) {
    printf("%s\n", dlerror());
  } else {
    printf("address of handle: %p\n", handle);
  }
  // std::cout << "<<< definitionso dlopened~ <<<\n";
  std::cout << "<<< now start loading libhalfso~ <<<\n";
  auto handle1 = dlopen(
      "/home/osboxes/playground/dlso/dlso/build/dlopen/halfso/libhalf.so",
      RTLD_NOW);
  if (!handle1) {
    printf("%s\n", dlerror());
  } else {

    printf("address of handle1: %p\n", handle1);
  }
  std::cout << "<<< halfso dlopened~ <<<\n";
}
