# DPA Utils

This library is still in it's alpha phase. Some APIs may still change significantly.

This library should work on any c17 compatible compiler. If c23 is available, it uses some C23 features too.  
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
Make sure to do a `make clean` before building the library is you use one of those files or a custom config.

You can open a shell in a build environment using `make shell`. It'll set `PATH` and `LD_LIBRARY_PATH`.
You can then run the example binaries without installing the library. You can also specify things like CC there,
and it'll carry over to any subsequent make calls in that shell.

You can create debug builds using `make debug=1`. You can create builds with asan enabled using `make asan=1`.
You can combine these options.

The files in `data/unicode/` are generated from unicode data files. See https://www.unicode.org/ucd/ for the
most recent version of those files. If those files are present in `/usr/share/unicode/` on your system,
then those files will be used. Otherwise, the files in `external/unicode/` will be used. It is also possible
to override the directory where the unicode data files to be used for this are located.  
For example: `make unicode_dir=/unicode/ data` will use the files in `/unicode/` for generating the ones in `data/unicode/`.

## Usage conventions

Any identifiers starting with `dpa__` (two underscores) or with `_`, is reserved, and should not be used.

There are some macro functions which can take a variety of types, thanks to generic selections. Most of them
also have a version suffixed with `_g`, those take any argument, and return an instance of `dpa_u_invalid_selection_t`
if the arguments are not supported. You can use them if you need to extend a function with generic selections, see also
`dpa_u_assert_selection`. The `_g` functions aren't all listed in the documentation.

Sometimes, there are also functions suffixed with `_p`. Those are regular functions, which are wrapped using a macro
which does not have the `_p` suffix.

## LICENSE

For the specifics, see the [COPYING](./COPYING) file.

The short version is, the library and everything is [MIT](LICENSE.MIT) licensed, including generated binaries,
but the unicode data files in `external/unicode/` use the [UNICODE V3](LICENSE.UNICODE) license,
and the files in `data/unicode/` are generated using the unicode data files, and use the same license as those files.
