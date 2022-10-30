#include "Half.h"
#include <iostream>

/** @attention: following definition duplicates with defintion in halfapp.cpp,
 * if libdefinition is dlopened, will use those definitions in halfapp.cpp
 * instead of following. It's like whoever first laoded has more weight, since
 * they are all strong symbols.
 */
Half::Half() { printf("Half ctor called~\n"); }
Half::~Half() { printf("Half dtor called~\n"); }

void Half::half_func() { printf("Half::half_func() called~\n"); }
Half d;
