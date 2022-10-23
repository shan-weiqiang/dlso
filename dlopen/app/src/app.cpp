#include "greet/inc/Greet.h"
#include <dlfcn.h>
#include <iostream>
#include <stdio.h>
/**
 * There is big dfference between a variable which is locally available inside
 * transilation unit and a variable that is dynamically linked elsewhere:
 * remark: this can be shown using ldd command to check if executable relies on
 * other so facts:
 * 1. if a variable is not linked from other so, eg, not extern, and ldd results
 * no dependent so(more accurate, shared libs with the same named and typed
 * variable), then the same variable in all so , including dlopened, have
 * individual address
 * 2. if a variable is not linked from other so, eg, not extern, however,
 * another ldd-dependet(namely, exe depend on this shared lib) shared lib has
 * the same variable(same type, same name), then the same variable in all shared
 * libs, including dlopened, have same address; different from using extern
 * keywords, every occurance of this same named and typed variable will
 * construct at this address
 * 3. if a variable is extern, means that the variable has to be found in other
 * so when starting up, then the same variable in all so, including dlopened(not
 * in the ldd dependency list), have the same address; and the extern ones will
 * not construct again; also, since it's extern, it means that it has to be
 * linked during compile time; also, the link is downwards, for example, let
 * variable be Type VarName; main exe has this variable(not extern): Type
 * VarName , shared lib A is exe's dependent lib and have extern Type VarName;
 * then lib A needs link another shared lib during compile time to find Type
 * VarName, not upwards to find it in main exe;
 * 4. since all shard libs are initialized before any initialization of main,
 * inlcuding globals initialization in main, as long as this Type VarName
 * variable is defined during program startup, then ODR, one definition rule
 * applies, all shared libs loaded after, if has Type VarName, share this
 * address. It's unique in the whole process.
 * 
 * summary:
 * 1. after process starts up, ODR rule apply to all variabel names between all
 *shared libs, if some of them not using extern, then constructor will be called
 *multi times, but in the same address
 * 2. when using dlopen in the middle of program, for Type VarName inside this
 *shared lib:
 * 	1. if  Type VarName already exit in the process, ODR applies
 * 		1. if has extern keywords: constructor will not be called again
 * 		2. if not has extern, constructor will be called again, in the
 *address of Type VarName
 *	2. if Type VarName does not exit in the process, Type VarName will be
 *constructed inside this shared lib
 *	3. if multi shared lib with this Type VarName is dlopened, Type VarName
 *exist individually inside these shared libs and have different addresses.
 *
 *
 */
extern "C" {
Greet g;
// 使用extern后，会在启动时加载test库，因为初始化程序会用到test库，不使用，则虽然主程序也有g，但是跟test中的是独立的
//使用dlopen打开的库，都会有自己的全局变量副本
// Greet g;

extern int a;
}
int main() {
  g.flag = 1;
  std::cout << '\n'
            << "<<< now dlopen libhello twice in main and dlopen libtest, "
               "before this are all "
               "printings of start time linking, since app is linked with "
               "libHello and libTest; following are dlopened so <<<\n";
  void *handle;
  handle =
      dlopen("/home/osboxes/playground/dlso/dlso/build/dlopen/dll/libHello.so",
             RTLD_NOW);
  void *handle1;
  handle1 =
      dlopen("/home/osboxes/playground/dlso/dlso/build/dlopen/dll/libHello.so",
             RTLD_NOW);
  void *handle2;
  //多次打开，不会初始化多次
  handle2 =
      dlopen("/home/osboxes/playground/dlso/dlso/build/dlopen/test/libtest.so",
             RTLD_NOW);
  if (!handle || !handle1 || !handle2) {
    printf("%s\n", dlerror());
  }

  std::cout
      << "<<< now end of dlopen libhello twice and libtest <<<\n"
      << "from main: a = " << a << std::endl
      << "address of app.a: " << &a
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
  void *p = dlsym(handle, "g");
  void *pt = (void *)&g;
  // 这个类似的，Hello.so和app都有全局的变量g，但是他们是互不影响的
  std::cout << "flag in Hello after loading twice : "
            << static_cast<Greet *>(p)->flag << "\n";
  std::cout << "address of g in Hello: " << p
            << "\n"; // g 在动态库映射虚拟内存区域
  std::cout << "address of g in main: " << &g << "\n";
  Greet c, d;
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
