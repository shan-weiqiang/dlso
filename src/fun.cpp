#include <iostream>
void anon_func();

void anon_func() { std::cout << "from anon_func~\n"; }

// it is a extern function
// even though the main app does not use this symbol, as long as the main app
// link this shared lib during compile time this symbol must be resolved
void another_func();

// this adds another_func() into .dyn-sym table
void func() { another_func(); }