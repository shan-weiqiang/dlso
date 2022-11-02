[TOC]

# about symbol table

1. symbols are a collection of items that describe where the name is defined and other attributes of symbols. It acts as index of all symbols of this object file and it can appear in any ELF section.  It includes:
   - symbols that are defined in this object file
   - symbols that are referenced by this object file
2.  only globals, including global function names and variables, and static local variables have names in symbol table; local variable do not have names in symbol table

3. `.symtab` and `.dynsym` section of ELF file store symbol table, difference:
   - `.symtab` stores all symbols; `.dynsym` stores symbols that to be used by dynamic linker: either symbols that provided by this object file or symbols that need to find in another shared libs.
   - `.symtab` do not need to load into memory during execution
   - `.dynsym` must be loaded into memory, and used to do dynamic symbol resolution
   - `.dynsym` is a subset of `.symtab`
4. compiler generate one symbol item whenever it encounter a global or static names during compilation
   - this means if one symbol is not used in program, compiler will not generate the symbol, for example, if only define `extern double data`, plus not using it inside any function, their will be no `data` symbol, because it is `extern` and never used inside this object file, meaning that it has no relationship with this object file. But if define `double data`, then `data` is valid symbol because, this means that this object file has a global name `data`

## more about `.dynsym`

1. by default, this table includes:

   - symbols that defined in other shared libs and used in this object file, for example, `extern double data`, plus `data` is used in this object file
   - symbols defined in this object file but are referenced by another shared lib
   - same name variables in  *dependent* shared libs (might be different type), in this case:
     - if variable has no constructor, such as `double data`, then the variable will be only initialized once; for example, `char hook='c'` exists in main program, `int hook = 32` in one shared libs that main program depends on, then the two variable have same address and works like a union.
     - if variable is a class that has constructor, then the constructor will be called at the same address multiple times
     - @attention: never let this happen. This the same with linking with .o files with same name variables, string, weak symol rule apply

2. use `-rdynamic` build flag to export all symbols

       -rdynamic
              Pass the flag -export-dynamic to the ELF linker, on targets that support it. This instructs the linker to add all symbols, not only used ones, to the dynamic symbol table. This option is needed for some uses of "dlopen" or to allow obtaining backtraces from within a program.



# facts got in the mud

For a given `Type VarName`:

 * if `Type VarName` is not linked from other shared lib, eg, not declared extern, and ldd command shows no dependent shared lib(more accurate, shared libs with `Type VarName` defined), then `Type VarName` in all shared lib , including dlopened, have individual addresses.
   * @remark: because in this scnario `Type VarName` is not in the `.dynsym`, not participate dynamic symbol resolution

 * if `Type VarName` is not linked from other shared lib, eg, not declared extern, however,another ldd-dependent(namely, exe depend on this shared lib, doesn't matter if this dependency is caused by `Type VarName` or not) shared lib has `Type VarName`, then `Type VarName` in all shared libs, including dlopened, have same address; different from the case which is declared as extern, every occurance of `Type VarName` will construct at this address
  * @remark: same variable name in dependent shared libs, the name will be added to `.dynsym` and participate dynamic symbol resolution

 * if `Type VarName` is declared extern, means that `Type VarName` has to be found in other shared libs when program starts, then `Type VarName` in all shared libs,including dlopened(not in the ldd dependency list), have the same address; and the extern ones will not construct again; also, since it's extern, it means that it has to be linked during compile time(not true for shared libs, extern variables in shared libs do not require linking during compile time, they can be dynamically linked during load time, definitions are also not indispensable for in compiling stage for shared libs, they also can be linked during load time, in summary, shared libs are compiled but have not been fully linked, but executables must be fully linked during compile time, so symbols that is used by the program, including symbols inside dependent shared libs must be fully defined. Besides, linking undefined symbols for definitions or extern variables inside a shared lib is the responsibility of the executable who use this shared lib.); Shared libs might have undefined functions and undefined variables(extern function and variables), this does not influence shared lib build, the executables who use this shared lib should be responsible for these undefined items at compile linking or dynamic linking. All symbols inside `.dynsym` table of dependent shared libs must be fully resolved.
  * @remark: at compile time , if target is executable, all symbols of this target and all `.dynsym` of dependent shared libs must be fully resolved.

 * since all shard libs are initialized before any initialization of main, including globals initialization in main, as long as this `Type VarName` variable is defined during program startup, then ODR, one definition rule applies, all shared libs loaded after, if has `Type VarName`, share this address. It's unique in the whole process.
   * @remark: ODR rule applies in compilation, link and execution


# dlopen

* when using dlopen in the middle of program, for `Type VarName` inside this shared lib in `.dynsym`:
    1. if  `Type VarName` already exit in the process, ODR applies
            1. if has extern keywords: constructor will not be called again
              2. if not has extern, constructor will be called again, in the address of `Type VarName`
      2. if `Type VarName` does not exit in the process,`Type VarName` will be constructed inside this shared lib
      3. if multi shared lib with this `Type VarName` is dlopened, `Type VarName` exist individually inside these shared libs and have different addresses.
* Since shared libs which are dlopened are not linked during compile time, so the executables does not know what symbols this dlopen shared lib have. This determines that all the symbol definition and extern variables can not depend on dlopened shared libs, because they have to be fully linked during compile time and startup phase. On the contrary, symbol definitions and extern variables inside dlopened shared libs must be linked by dynamic linker obeying ODR rule. If shared lib that is dlopened has undefined symbol(must be used by the executable, for example in the ctor of globals of this lib, or in __((constructor))__), plus these symbols can not find definition by the executable(they might be found in executable itself or in one of dependent shared libs), there will be a undefined symbol error(can be printed using printf("%s\n", dlerror());
* Besides, dlopened shared libs do NOT share symbols between each other(peer to peer), for example, libA has undefined symbol S, libB has this symbol S defined, executable first dlopen libA, then dlopen libB, there still will be undefined symbol error for symbol S in libB. Executable can only find definitions in itself or in shared libs which are linked during compile time. They also do not shared symbols between each other(parent to son), for example, shared lib A is dlopened, A dlopen B, then symbols in A will not be shared by B.
* Executables will share all symbols with dlopened libs, for example, if there are same symbols in executable(including compile time shared libs) and dlopened shared libs, if they are all strong symbols, those in executables will be used for dlopened shred libs.
