# CMake target_link_libraries() scopes example

An example of particular effects from `PRIVATE`/`INTERFACE`/`PUBLIC` scope in CMake's `target_link_libraries()`.

More details in the [following article](https://decovar.dev/blog/2023/07/22/cmake-target-link-libraries-scopes/).

Unlike the code fragments in the article, the `prjct` here handles linking scope via `THINGY_LINKING` cache variable, for example `-DTHINGY_LINKING="INTERFACE"`. Based on that, certain target properties are set and carried over, changing certain compile definitions, making the compilation to account for the current linking scope "automatically" (*so you don't need to modify the sources yourself*).

## Building

It is 3 projects that are built individually and in particular order:

1. `dpndnc` - a library made to be a direct dependency of `prjct`;
2. `prjct` - a project with two libraries, one of which directly depends on `dpndnc`;
3. `tl` - a CLI tool that directly depends on `prjct` libraries and also transitively depends on `dpndnc`.

### dpndnc

``` sh
$ cd /path/to/cmake-target-link-libraries-example/dpndnc
$ mkdir build && cd $_
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="../install" ..
$ cmake --build . --target install
```

### prjct

``` sh
$ cd /path/to/cmake-target-link-libraries-example/prjct
$ mkdir build && cd $_
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="../install" -DCMAKE_PREFIX_PATH="/path/to/cmake-target-link-libraries-example/dpndnc/install" -DTHINGY_LINKING="INTERFACE" ..
$ cmake --build . --target install
```

### tl

``` sh
$ cd /path/to/cmake-target-link-libraries-example/tl
$ mkdir build && cd $_
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="../install" -DCMAKE_PREFIX_PATH="/path/to/cmake-target-link-libraries-example/prjct/install;/path/to/cmake-target-link-libraries-example/dpndnc/install" ..
$ cmake --build . --target install
$ ../install/bin/some-tool
```
