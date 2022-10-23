#include "dlfcn.h"
#include "greet/inc/Greet.h"
#include <dlfcn.h>
#include <stdio.h>

extern "C" {
 Greet g;
// 这里如果用了extern，则指向了test中的g，不会重复构造
// Greet g;
// 如果不使用extern，但是主程序中使用了extern，这里会重新构造，但是构造地址跟test中的g地址一样？！!!!!!
// 猜测原因：
// 1. 当使用extern，则编译器知道这个是外面单元的g，test中有g，则不会重新构造
// 2. -
// 如果主程序extern一个外部变量，且已经加载并初始化；此时如果有另外一个动态库也有这个全局变量
// - 如果在这个动态库中该变量是extern的，则不会重新构造，使用现有的变量
// -
// 如果这个动态库中该变量不是extern的，则会重新构造，**但是其地址跟主程序以及另外一个动态库地址一致**
//     -
//     此种情况下其实是外部主程序需要找到一个外部的全局变量（因为使用了extern），但是有两个动态库提供了这个选项，都有该名称的变量，并且都不是extern的，所以，对于主程序来说，会在编译链接时给定一个该变量一个地址（在主程序虚拟内存区域），当动态库被加载，且有符号要求的变量，就会在给定的这个地址对这个变量进行初始化
//     -
//     也就是说，主程序在连接时候已经为该变量的初始化提供了地址，运行时会等待符合要求的动态库来初始化，当符合要求的动态库有多个时，就会在这个位置调用多次构造函数，初始化多次
}
static Greet q;
static int a = 0;
void test(); // 只有声明，没有实现也能编译通过，会在运行时查找
void __attribute__((constructor)) fn();
void __attribute__((constructor)) fn() {
  printf("<<< now libhello-->((constructor)) called~\n");
  printf("<<< now dlopen libtest two times\n");
  /** @attention: even dlopened twice, libtest's ((constructor)) and global
   * variable initialization will be called once; second time dlopen has no
   * effect
   */
  void *handle;
  handle =
      dlopen("/home/osboxes/playground/dlso/dlso/build/dlopen/test/libtest.so",
             RTLD_NOW);
  void *handle1;
  handle1 =
      dlopen("/home/osboxes/playground/dlso/dlso/build/dlopen/test/libtest.so",
             RTLD_NOW);
  if (!handle || !handle1) {
    printf("%s\n", dlerror());
  }
  printf("<<< now end of dlopen libtest two times\n");
  Greet::sflag = 10;
  printf("Greet::sflag:%d\n", Greet::sflag);
  printf("address of Greet::sflag from Hello.so:%p\n", &Greet::sflag);
  printf("address of g in libhello: %p\n", &g);
  printf("<<< now end of libhello-->((constructor)) <<<\n\n");
  printf(
      "<<< now Greet g and q will be constructed in order\n");
  //在Hello.so的内存映射区域，说明从静态库内部访问全局变量的静态成员，访问的是动态库自己的静态成员；
  //而如果用dlsym找到这个全局变量，并在主程序中访问这个变量的静态成员，则是访问的主程序的静态成员
}
