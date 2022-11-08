
# dlopen

## document

function call: `void *dlopen(const char *filename, int flag);`

flag options and meanings:

1. RTLD_LAZY
   Perform lazy binding. Only resolve symbols as the code that references them is executed. If the symbol is never referenced, then it is never resolved. (Lazy binding is only performed for function references; references to variables are always immediately bound when the library is loaded.)
2. RTLD_NOW
   If this value is specified, or the environment variable LD_BIND_NOW is set to a nonempty string, all undefined symbols in the library are resolved before dlopen() returns. If this cannot be done, an error is returned.

Zero or more of the following values may also be ORed in flag:

1. RTLD_GLOBAL
   The symbols defined by this library will be made available for symbol resolution of *subsequently loaded libraries*.
2. RTLD_LOCAL
   This is the converse of RTLD_GLOBAL, and the default if neither flag is specified. Symbols defined in this library are not made available to resolve references in *subsequently loaded libraries*.
3. RTLD_NODELETE (since glibc 2.2)
   Do not unload the library during dlclose(). Consequently, the library's static variables are not reinitialized if the library is reloaded with dlopen() at a later time. This flag is not specified in POSIX.1-2001.
4. RTLD_NOLOAD (since glibc 2.2)
   Don't load the library. This can be used to test if the library is already resident (dlopen() returns NULL if it is not, or the library's handle if it is resident). This flag can also be used to promote the flags on a library that is already loaded. For example, a library that was previously loaded with RTLD_LOCAL can be reopened with RTLD_NOLOAD | RTLD_GLOBAL. This flag is not specified in POSIX.1-2001.
5. RTLD_DEEPBIND (since glibc 2.3.4)
   Place the lookup scope of the symbols in this library ahead of the global scope. This means that a self-contained library will use its own symbols in preference to global symbols with the same name contained in libraries that have already been loaded. This flag is not specified in POSIX.1-2001.

If filename is a NULL pointer, then the returned handle is for the main program. When given to dlsym(), this handle causes a search for a symbol in the main program, followed by all shared libraries loaded at program startup, and then all shared libraries loaded by dlopen() with the flag RTLD_GLOBAL.

External references in the library are resolved using the libraries in that library's dependency list and any other libraries previously opened with the RTLD_GLOBAL flag. If the executable was linked with the flag "-rdynamic" (or, synonymously, "--export-dynamic"), then the global symbols in the executable will also be used to resolve references in a dynamically loaded library.

If the same library is loaded again with dlopen(), the same file handle is returned. The dl library maintains reference counts for library handles, so a dynamic library is not deallocated until dlclose() has been called on it as many times as dlopen() has succeeded on it. The _init() routine, if present, is only called once. But a subsequent call with RTLD_NOW may force symbol resolution for a library earlier loaded with RTLD_LAZY.

If dlopen() fails for any reason, it returns NULL.

## more about RTLD_LOCAL and RTLD_GLOBAL

1. no matter `RTLD_LOCAL` or `RTLD_GLOBAL`, when the main program `dlopen` one shared lib, symbols inside this shared lib will be resolved against symbols in `.dynsym` of main program itself and all dependent load time shared libs
2. when `RTLD_GLOBAL` is specified, symbols inside `.dynsym` of this shared lib will be used to resove *subsequenly loaded* shared libs. **This means that two dlopened shard libs might interdependent**
3. when using dlopen in the middle of program, for `Type VarName` inside this shared lib in `.dynsym`:
4. if  `Type VarName` already exist in the process，**in the main program object file or any dependent shared libs**, ODR applies

   1. if has extern keywords: constructor will not be called again
   2. if not has extern, constructor will be called again, in the address of `Type VarName`
   3. if `Type VarName` does not exist in the process,`Type VarName` will be constructed inside this shared lib
   4. if multi shared lib with this `Type VarName` is dlopened, the behavior depends on flags used when using dlopen
5. Since shared libs which are dlopened are not linked during compile time, so the executables does not know what symbols this dlopen shared lib have. This determines that all the symbol definition and extern variables can not depend on dlopened shared libs, because they have to be fully linked during compile time and startup phase. On the contrary, symbol definitions and extern variables inside dlopened shared libs must be linked by dynamic linker. If shared lib that is dlopened has undefined symbol(must be used by the executable, for example in the ctor of globals of this lib, or in **((constructor))**; *remark later: otherwise there will not have this symbol !* ), plus these symbols can not find definition by the executable(they might be found in executable itself or in one of dependent shared libs), there will be a undefined symbol error(can be printed using printf("%s\n", dlerror());
6. symbol sharing:

   - peer to peer: symbol resolve between dlopened shared libs are controlled by dlopen flags(`RTLD_LOCAL`, `RTLD_GLOBAL`..)
   - parent to son: **first dlopen A, A dlopen B, even A use `RTLD_GLOBAL`, symbols in A will not share with B**
7. Executables will share all symbols with dlopened libs, for example, if there are same symbols in executable(including compile time shared libs) and dlopened shared libs, if they are all strong symbols, those in executables will be used for dlopened shared libs.