#include "shareddata.h"
#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

/** myclass will be initialized again here, even though be move assigned in
 * _attribute_((constructor))
 */
SomeClass myclass{1};
InnerClass SomeClass::inner;

__attribute__((constructor)) void dlopen_function() {
  /** @attention: at this phase, static InnerClass inner has not been
   * initialized!!
   */
  std::cout << "<<< now call somelib-->((constructor))<<<\n"
            << "here myclass will be constructed, tem SomeClass will be "
               "destructed!, without invoving static inner:\n";
  myclass = SomeClass(2);
  std::cout << "<<< end of somelib-->((constructor))<<<\n"
            << "<<<global variable constructor and static member "
               "initializiation begins: <<<\n";
}
__attribute__((destructor)) void dclose_function() {
  std::cout << "<<< now start dlclose somelib<<<\n"
            << "<<<now call somelib--> ((destructor))<<<\n"
            /** myclass.a == 1
             */
            << "address of myclass in somelib: " << &myclass << std::endl
            << "value of myclass.a: " << myclass.a << std::endl
            << "address of static inner: " << &SomeClass::inner << std::endl
            << "value of static : " << SomeClass::inner.a << std::endl
            << "<<< end of somelib -->((destructor))<<<\n"
            << "<<<now starting calling destructor of myclass and innner<<<\n";
}
