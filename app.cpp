#include "shareddata.h"
#include <dlfcn.h>
#include <iostream>

/**
 * @attention: by default static memember initializaiton is independent of
 * object declareation here we can declare myclass before static memeber
 * initialization!!
 */
SomeClass myclass{0};
InnerClass SomeClass::inner;

int main() {
  SomeClass::inner.a = 10;
  std::cout << "following lines are called after calling constructor of "
               "myclass and inner:\n"
            << "address of static inner in main: " << &SomeClass::inner << '\n'
            << "value of static inner: " << SomeClass::inner.a << '\n'
            << "address of myclass in main: " << &myclass << '\n'
            << '\n';
  /**
   * before return of dlopen:
   * 1. first call _attribute_((constructor))
   * @attention: following step is not guaranteed execute before return of
   * dlopen
   * 2. second call global varialble constructors
   * 	1. first call non-static member constructors
   * 	2. second call global variable constructor
   * 	3. last call static memeber constructor (depends on where static
   * initialization, can be before step 1,2)
   * @attention: initialize global varialbe inside _attribute_((constructor))
   * will NOT prevent initialize it again. after return of
   * _attribute_((constructor)), global variables will be initialized again
   *
   */
  auto handle =
      dlopen("/home/osboxes/playground/dlso/dlso/build/somelib/libsomelib.so",
             RTLD_NOW);
  std::cout << "address of handle: " << handle << std::endl
            << "somelib dlopened from main~\n"
            << '\n'
            << "<<< start dlopen secondlib~ <<<\n";
  auto handle_secondlib = dlopen(
      "/home/osboxes/playground/dlso/dlso/build/secondlib/libsecondlib.so",
      RTLD_NOW);

  std::cout << "address of handle_secondlib: " << handle_secondlib << std::endl
            << "secondlib dlopened from main~\n"
            << '\n'
            << "***now starting dlclose phase~***\n"
            << '\n';
  /** before return of dlclose:
   * 1. first call _attribute_((destructor))
   * @attention: following destructor execution is not guaranteed before dlclose
   * return
   * 2. second call global variable destructor
   * 	1. first call static-member destructor(depends on where static
   * initialization, can be after step 2,3)
   * 	2. second call global variable destructor
   * 	3. last call non-static memeber destructor
   * @attention: destructor is called reversely compared to constructor
   */
  dlclose(handle);
  std::cout << '\n' << "<<< now start dlclose secondlib <<<\n";
  dlclose(handle_secondlib);
  std::cout
      << "\ndlclosed from main~\n"
      << '\n'
      << "<<< now start call destructors of myclass and innner from main\n";
}
