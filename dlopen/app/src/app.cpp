#include "greet/inc/Greet.h"
#include "sample.h"
#include <dlfcn.h>
#include <iostream>
#include <stdio.h>

/**
 * There is big dfference between a variable which is locally available inside
 * transilation unit and a variable that is dynamically linked elsewhere:
 * remark: this can be shown using ldd command to check if executable relies on
 * other so.
 *
 * @attention: symbols have different types for the same name, some name is
 undefined(U), some is D(data section), some is T(text), only those used in
 actual program(instructions) have symbols.
 *
 * For a given Type VarName:
 *
 * 1. if Type VarName is not linked from other shared lib, eg, not declared
 extern, and ldd command shows no dependent shared lib(more accurate, shared
 libs with Type VarName defined), then Type VarName in all shared lib ,
 including dlopened, have individual addresses.

 * 2. if Type VarName is not linked from other shared lib, eg, not declared
 extern, however,another ldd-dependent(namely, exe depend on this shared lib,
 doesn't matter if this dependency is caused by Type VarName or not) shared lib
 has Type VarName, then Type VarName in all shared libs, including dlopened,
 have same address; different from the case which is declared as extern, every
 occurance of Type VarName will construct at this address

 * 3. if Type VarName is declared extern, means that Type VarName has to be
 found in other shared libs when program starts, then Type VarName in all shared
 libs,including dlopened(not in the ldd dependency list), have the same address;
 and the extern ones will not construct again; also, since it's extern, it means
 that it has to be linked during compile time(not true for shared libs, extern
 variables in shared libs do not require linking during compile time, they can
 be dynamically linked during load time, definitions are also not indespensible
 for in compiling stage for shared libs, they also can be linked during load
 time, in summary, shared libs are compiled but have not been fully linked, but
 executables must be fully linked during compile time, so symbols that is used
 by the program, including symbols inside dependent shared libs must be fully
 defined. Besides, lingking undefined symbols for definitions or extern
 variables inside a shared lib is the responsibility of the executable who use
 this shared lib.); Shared libs might have undefined functions and undefined
 variables(extern function and variables), this does not influence shared lib
 build, the executables who use this shared lib should be responsible for these
 undefined items at compile linking or dynamic linking, according to which part
 of this shared lib the executable use. It's like as it is theory, shared lib
 provide as it is, executable who use it is responsible for linking. The unused
 part of the shared lib, even is undefined, does not influence the executable.

 * 4. since all shard libs are initialized before any initialization of main,
 inlcuding globals initialization in main, as long as this Type VarName variable
 is defined during program startup, then ODR, one definition rule applies, all
 shared libs loaded after, if has Type VarName, share this address. It's unique
 in the whole process.

 * summary:
 * 1. after process starts up, ODR rule apply to all variabel names between all
 shared libs, if some of them not using extern, then constructor will be called
 multi times, but in the same address

 * 2. when using dlopen in the middle of program, for Type VarName inside this
 shared lib:
        1. if  Type VarName already exit in the process, ODR applies
                1. if has extern keywords: constructor will not be called again
                2. if not has extern, constructor will be called again, in the
 address of Type VarName
        2. if Type VarName does not exit in the process,Type VarName will be
 constructed inside this shared lib
        3. if multi shared lib with this Type VarName is dlopened, Type VarName
 exist individually inside these shared libs and have different addresses.

 * one more thing about dlopen:
 * Since shared libs which are dlopened are not linked during compile time, so
 the executables does not know what symbols this dlopen shared lib have. This
 determines that all the symbol definition and extern variables can not depend
 on dlopened shared libs, because they have to be fully linked during compile
 time and startup phase. On the contrary, symbol definitions and extern
 variables inside dlopened shared libs must be linked by dynamic linker obeying
 ODR rule. If shared lib that is dlopened has undefined symbol(must be used by
 the executable, for example in the ctor of globals of this lib, or in
 __((constructor))__), plus these symbols can not find definition by the
 executable(they might be found in executable itself or in one of dependent
 shared libs), there will be a undefined symbol error(can be printed using
 printf("%s\n", dlerror());

 Besides, dlopened shared libs do NOT share symbols between each
 other(peer to peer), for example, libA has undefined symbol S, libB has this
 symbol S defined, executable first dlopen libA, then dlopen libB, there still
 will be undefined symbol error for symbol S in libB. Executable can only find
 definitions in itself or in shared libs which are linked during compile time.
 They also do not shared symbols between each other(parent to son), for example,
 shared lib A is dlopened, A dlopen B, then symbols in A will not be shared by
 B.

 Executables will share all symbols with dlopened libs, for example, if there
 are same symbols in executable(including compile time shared libs) and dlopened
 shared libs, if they are all strong symbols, those in executables will be used
 for dlopened shred libs.

 For load time shared libs, because they are linked during compile time, all
 there symbols are combined with executables, this means all the symbols, even
 they are not used by executables, must be fully linked(defined); Symbol tables
 are combined during compile time for executable and shared libs. ps: if first
 compile with a shared lib, then add some undefined symbol in this same lib and
 only compile this lib but without recompile the executable, then the executable
 can run successfully, this means that during load time, the dynamic linker does
 not recombine symbol table with the executable, it only relocates the GOT table
 of the executable. For dloped shared libs, if RTLD_NOW is used, then all
 symbols, including these not used, must be resolved. If RTLD_LAZY is used, then
 only during execution the symbols be resolved.

 If not compile using --export-dynamic option, only those symbols that are
 referenced by other shared libs are in the .dynsym table, such as same name
 globals, functions that is refernced etc. Otherwise, symbols only exist in
 .symtab.
 *
 *
 */
extern "C" {
/** @attention: must use printf instead of std::cout, since this function will
 * be called by a dependent shared lib, when this  lib is initialized, std::cout
 * is not accessible.
 */
void func_without_definition(double a) { printf("hah\n"); }
Greet g;
// 使用extern后，会在启动时加载test库，因为初始化程序会用到test库，不使用，则虽然主程序也有g，但是跟test中的是独立的
//使用dlopen打开的库，都会有自己的全局变量副本
// Greet g;

int a;
extern int b;
}
SampleStruct::SampleStruct() { printf("SampleStruct ctor called~\n"); }
SampleStruct::~SampleStruct() { printf("SampleStruct dtor called~\n"); }
void SampleStruct::somefunc() { printf("SampleStruct::somefunc() called~\n"); }
int main() {
  g.flag = 1;
  std::cout << '\n'
            << "<<< now dlopen libhello twice in main and dlopen libtest, "
               "before this are all "
               "printings of start time linking, since app is linked with "
               "libHello and libTest; following are dlopened so <<<\n";
  void *handle;
  handle = dlopen(
      "/home/osboxes/playground/dlso/dlso/build/dlopen/hello/libHello.so",
      RTLD_NOW);
  if (!handle) {
    printf("%s\n", dlerror());
  }
  void *handle1;
  handle1 = dlopen(
      "/home/osboxes/playground/dlso/dlso/build/dlopen/hello/libHello.so",
      RTLD_NOW);
  if (!handle1) {
    printf("%s\n", dlerror());
  }
  void *handle2;
  //多次打开，不会初始化多次
  handle2 =
      dlopen("/home/osboxes/playground/dlso/dlso/build/dlopen/test/libtest.so",
             RTLD_NOW);
  if (!handle2) {
    printf("%s\n", dlerror());
  }
  /** @attention: do not use dlerror() in following way, segmentation fault
   */
  // if (!handle || !handle1 || !handle2) {
  //   printf("%s\n", dlerror());
  //   std::cout << "address of libHello.so: " << handle << '\n';
  //   std::cout << "program sucess here~\n";
  //   fflush(stdout);
  //   fflush(stderr);
  // }

  std::cout
      << "<<< now end of dlopen libhello twice and libtest <<<\n"
      << "from main: a = " << a << std::endl
      << "address of app.a: " << &a << '\n'
      << "address of app.b: " << &b
      << "\n"
      // app和test.so中都有int
      // a全局变量，但是他们是不相关的，地址不在统一区域；app的a是在全局变量区域；test的a是在动态库的映射区域
      << "address of g in main: " << &g << '\n'
      << "flag in main after loading Hello.so: " << g.flag << "\n"
      << "static flag in main after loading Hello.so: " << Greet::sflag << "\n"
      << "address of static flag in main: " << &Greet::sflag << '\n';
  auto handle_indep = dlopen("/home/osboxes/playground/dlso/dlso/build/dlopen/"
                             "independentso/libindep.so",
                             RTLD_NOW);
  if (!handle_indep) {
    printf("%s\n", dlerror());
  }
  /** @attention: even handle == 0, dlsym stll can get address,!!
   */
  void *p = dlsym(handle, "g");
  void *pt = (void *)&g;
  // 这个类似的，Hello.so和app都有全局的变量g，但是他们是互不影响的
  /** @attention: here if g in handle is extern, using dlsym and static_cast to
   * access will segmentation fault, because it extern, there is no memory
   * allocated in that address!
   */
  // std::cout << "flag in Hello after loading twice : "
  //           << static_cast<Greet *>(p)->flag << "\n";
  std::cout << "address of g in Hello using dlsym: " << p
            << "\n"; // g 在动态库映射虚拟内存区域
  /** @attention: if p points to extern variable, following address is actually
   * not in the address space, dereference will segmentation fault
   */
  std::cout << "static g.sflag in Hello.so address: "
            << &(static_cast<Greet *>(p)->sflag)
            << "\n"; // 其静态成员在常量区，在主程序区域
  std::cout
      << "static g.sflag in main address: " << &(g.sflag)
      << "\n"; // 与上面一致，说明动态库中的静态成员跟主程序的静态成员是同一个，并且在主程序中
  std::cout << "Greet::sflag: " << Greet::sflag << "\n";
  std::cout << "static g.sflag in Hello.so: " << static_cast<Greet *>(p)->sflag
            << "\n";

  std::cout << "address of flag in main: " << &(g.flag) << "\n";
  std::cout << "address of flag in Hello: " << &(static_cast<Greet *>(p)->flag)
            << "\n";
  // 上面两个地址是不同的，说明同名的全局变量，动态库和主程序仍然是不同的，分别存储在不同的区域，动态库在动态库mapping区域
}
