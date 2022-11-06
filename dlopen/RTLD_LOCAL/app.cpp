#include "SomeClass.h"
#include <dlfcn.h>
#include <stdio.h>

// SomeClass someclass;
// extern int a;

int main(int argc, char const *argv[])
{
    auto first_handle = dlopen("./build/libfirst.so", RTLD_NOW | RTLD_GLOBAL);
    if (!first_handle)
    {
        printf("%s\n", dlerror());
    }

    /**
     * @brief this line add variable a into .dynsym
     *
     */
    // printf("%u\n", a);

    return 0;
}
