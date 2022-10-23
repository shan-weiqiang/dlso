#include "greet/inc/Greet.h"
#include <iostream>

int Greet::sflag = 0;
Greet::Greet(){
    std::cout << "Hello~ from :" << this << "\n";
    sflag++;
}

Greet::~Greet(){
    std::cout << "Bye~\n";
}