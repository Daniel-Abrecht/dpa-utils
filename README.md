# DPA Utils

This is going to be a library with a lot of useful utility functions.

This library should with on any c17 compatible compiler. If c23 is qavailable, it uses some C23 features too.  
It has been tested with clang and gcc on linux. msvc is explicitly not supported. You can use clang or gcc to cross
compile it to windows, but you can't do it with the windows ABI.  

There is one implementation & target specific assumption made in this library. Currently, the tagged pointer
functionality assumes the most significant byte of a pointer is always 0 after converting it to a uint64_t,
and that a pointer can be converted to an uint64_t and back.

## Building & installing the library

Just build & install it:

```sh
make
sudo make install
```

There are also some testcases you may want to run before installing it, using `make test`.

To build the documentation, use `make docs`, it will be placed in `build/docs/api/`.
This requires doxygen to be installed.

Some platforms may need some additional compiler options & config options. Take a look at the `mk/` and `config/` directories.
If you use a config when building the library, make sure the same one is used when you build any program which uses it.
Also take a look at the dpa/utils/config.h file for what you can put in there.

To use one of the files in the `mk/` folder, you can specify it in the make command. For example `make use=avr`.
Make sure to do a `make clean` before building the libtary is you use one of those files or a custom config.

You can open a shell in a build environment using `make shell`. It'll set `PATH` and `LD_LIBRARY_PATH`.
You can then run the example binaries without installing the library. You can also specify things like CC there,
and it'll carry over to any subsequenbt make calls in that shell.

You can create debug builds using `make debug=1`. You can create builds with asan enabled using `make asan=1`.
You can combine these options.

## Usage conventions

Any identifiers starting with `dpa__` (two underscores) or with `_`, is reserved, and should not be used.

There are some macro functions which can take a variety of types, thanks to generic selections. Most of them
also have a verison suffixed with `_g`, those take any argument, and return an instance of \ref dpa_u_invalid_selection_t
if the arguments are not supported. You can use them if you need to extend a function with generic selections, see also
\ref dpa_u_assert_selection. The `_g` functions aren't all listed in the documentation.

Sometimes, there are also functions suffixed with `_p`. Those are regular functions, which are wrapped using a macro
which does not have the `_p` suffix.
