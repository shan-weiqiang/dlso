#include "SomeClass.h"

#include <stdio.h>

extern SomeClass someclass;

void second_some_func()
{
    printf("%p\n", &someclass);
}