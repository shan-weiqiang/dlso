#include "shareddata.h"

SomeClass myclass{3};
// InnerClass SomeClass::inner;
__attribute__((destructor)) void destructor_func() {
  std::cout << "<<< start call secondlib-->((destructor))\n"
            << "address of myclass in secondlib: " << &myclass << std::endl
            << "myclass.a from secondlib: " << myclass.a << std::endl
            << "<<< end of secondlib -->((destructor))\n"
            << "<<<now start call destructor of myclass<<<\n";
  /** @attention: following line will cause a segmentation fault!! Because,
   * there is no static inner in this shared library, this again shows that
   * different translation unit have their own static variable!! If we also
   * decare a static inner in this file, the seg fault will be gone.
   */
  // std::cout << "address of static inner: " << &SomeClass::inner << std::endl;
}
