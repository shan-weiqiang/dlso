
# about symbol table

1. symbols are a collection of items that describe where the name is defined and other attributes of symbols. It acts as index of all symbols of this object file and it can appear in any ELF section.  It includes:
   - symbols that are defined in this object file
   - symbols that are referenced by this object file
2. only globals, including global function names and variables, and static local variables have names in symbol table; local variable do not have names in symbol table
3. `.symtab` and `.dynsym` section of ELF file store symbol table, difference:
   - `.symtab` stores all symbols; `.dynsym` stores symbols that to be used by dynamic linker: either symbols that provided by this object file or symbols that need to find in another shared libs.
   - `.symtab` do not need to load into memory during execution
   - `.dynsym` must be loaded into memory, and used to do dynamic symbol resolution
   - `.dynsym` is a subset of `.symtab`
4. compiler generate one symbol item whenever it encounter a global or static names during compilation
   - this means if one symbol is not used in program, compiler will not generate the symbol, for example, if only define `extern double data`, plus not using it inside any function, their will be no `data` symbol, because it is `extern` and never used inside this object file, meaning that it has no relationship with this object file. But if define `double data`, then `data` is valid symbol because, this means that this object file has a global name `data`

## difference between compilation linking and dynamic linking

1. link at compilation time obeys ODR strictly, if multi-definition is found there will be errors
2. link at dynamic is different, at this time there might be multi-definitions of on symbol, the linker's job is to relocate every symbol to the right position. For example, when dlopen shared libs, there might be same symbols, the linker will determine where the symbol points to.

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

3. note that `-rdynamic` is only used to pass `-export-dynamic` link option to the linker, so in `cmake` projects, two add options have to be used for this function: `target_compile_options(app PUBLIC -rdynamic)` and `target_link_options(app PUBLIC -export-dynamic)`, because `cmake` add these two options separately.

# facts got in the mud

For a given `Type VarName`:

- if `Type VarName` is not linked from other shared lib, eg, not declared extern, and ldd command shows no dependent shared lib(more accurate, shared libs with `Type VarName` defined), then `Type VarName` in all shared lib , including dlopened(need to consider `RTLD_LOCAL`, `RTLD_GLOBAL` flag), have individual addresses.
  - @remark: because in this scnario `Type VarName` is not in the `.dynsym`, not participate dynamic symbol resolution

- if `Type VarName` is not linked from other shared lib, eg, not declared extern, however,another ldd-dependent(namely, exe depend on this shared lib, doesn't matter if this dependency is caused by `Type VarName` or not) shared lib has `Type VarName`, then `Type VarName` in all shared libs, including dlopened, have same address; different from the case which is declared as extern, every occurance of `Type VarName` will construct at this address
  - @remark: same variable name in dependent shared libs, the name will be added to `.dynsym` and participate dynamic symbol resolution

- if `Type VarName` is declared extern, means that `Type VarName` has to be found in other shared libs when program starts, then `Type VarName` in all shared libs,including dlopened(not in the ldd dependency list. need to consider `RTLD_LOCAL`, `RTLD_GLOBAL` flag), have the same address; and the extern ones will not construct again; also, since it's extern, it means that it has to be linked during compile time(not true for shared libs, extern variables in shared libs do not require linking during compile time, they can be dynamically linked during load time, definitions are also not indispensable for in compiling stage for shared libs, they also can be linked during load time, in summary, shared libs are compiled but have not been fully linked, but executables must be fully linked during compile time, so symbols that is used by the program, including symbols inside dependent shared libs must be fully defined. Besides, linking undefined symbols for definitions or extern variables inside a shared lib is the responsibility of the executable who use this shared lib.); Shared libs might have undefined functions and undefined variables(extern function and variables), this does not influence shared lib build, the executables who use this shared lib should be responsible for these undefined items at compile linking or dynamic linking. All symbols inside `.dynsym` table of dependent shared libs must be fully resolved.
  - @remark: at compile time , if target is executable, all symbols of this target and all `.dynsym` of dependent shared libs must be fully resolved.

- since all shard libs are initialized before any initialization of main, including globals initialization in main, as long as this `Type VarName` variable is defined during program startup, then ODR, one definition rule applies, all shared libs loaded after, if has `Type VarName`, share this address. It's unique in the whole process.
  - @remark: ODR rule applies in compilation, link and execution

# inline and symbols

1. inline functions are designed to be flatted out in the calling function, without call stack, so the definition means that there isn't a symbol for the inline functions; Suppose there is a symbol for the inline function, then this symbol is reference by another object file, then the function code for this symbol must be seperated from the calling function, which is exactly against the definition of inline
2. class methods that are defined inside `class {}` are inline functions by default, so there will be no symbols for these methods
3. class with declaration(header file) and definition(cpp file) seperated are not inline functions, this is the normal way for create shared libs.
4. **inline is just a recommandation for compiler**

# template and shared libs and symbols

1. the essence of templates are that the definitions(code) are generated by compilers during compiling time, according to the specific type the user use; This characteristic determines that:
   - if use templates as shared lib, one has to explicitly instantiate all the types that are going to be provided by this shared lib, because without explicitly instantiation, the code doesn't even exist
   - the result is that the use of the template is limited within the explicitly instantiated types, so it's actually against the design of template, which aims to be compatible with unlimited use cases
   - **the normal way to use template is to include template declaration and definition in the header file and compile all code into the object file that actually use these templates**
2. for template, since the code is generated by compiler, the compiler actually is very  lazy:
   - it only generates those function code that are really need to be instantiated
   - for those functions that are not called(instantiated), compiler will not produce them
3. for non-template, in other words, user defined functions, the compiler respects the user’s work; This means no matter the function is called or not, compiler will generate code of these functions
4. no matter template of non-template, inline functions have no symbols
