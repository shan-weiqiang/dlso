#include "SomeClass.h"
#include <dlfcn.h>
#include <stdio.h>

SomeClass someclass;

void __attribute__((constructor)) user_open()
{
    auto second_handle = dlopen("./build/libsecond.so", RTLD_NOW | RTLD_LOCAL);
    if (!second_handle)
    {
        printf("%s\n", dlerror());
    }
}
