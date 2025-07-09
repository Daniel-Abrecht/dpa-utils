# DPA Utils

This is going to be a library with a lot of useful utility functions.

This library should work on any c17 compatible compiler. If c23 is qavailable, it uses some C23 features too.  
It has been tested with clang and gcc on linux. msvc is explicitly not supported. You can use clang or gcc to cross
compile it to windows, but you can't do it with the windows ABI.

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

To use one of the files in the `mk/` folder, you can specify it in the make command. For example `make use=avr`.
Make sure to do a `make clean` before building the libtary is you use one of those files or a custom config.

You can open a shell in a build environment using `make shell`. It'll set `PATH` and `LD_LIBRARY_PATH`.
You can then run the example binaries without installing the library. You can also specify things like CC there,
and it'll carry over to any subsequenbt make calls in that shell.

You can create debug builds using `make debug=1`. You can create builds with asan enabled using `make asan=1`.
You can combine these options.
