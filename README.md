# CMake target_link_libraries() scopes example

An example of particular effects from `PRIVATE`/`INTERFACE`/`PUBLIC` scope in CMake's `target_link_libraries()`.

More details in the [following article](https://decovar.dev/blog/2023/07/15/cmake-target-link-libraries-scope/).

## Building

### dpndnc

``` sh
$ cd /path/to/cmake-target-link-libraries-example
$ mkdir build && cd $_
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="../install" ..
$ cmake --build . --target install
```

### prjct

``` sh
$ cd /path/to/cmake-target-link-libraries-example
$ mkdir build && cd $_
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="../install" -DCMAKE_PREFIX_PATH="/path/to/cmake-target-link-libraries-example/dpndnc/install" -DTHINGY_LINKING="INTERFACE" ..
$ cmake --build . --target install
```

### tl

``` sh
$ cd /path/to/cmake-target-link-libraries-example
$ mkdir build && cd $_
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="../install" -DCMAKE_PREFIX_PATH="/path/to/cmake-target-link-libraries-example/prjct/install;/path/to/cmake-target-link-libraries-example/dpndnc/install" ..
$ cmake --build . --target install
$ ../install/bin/some-tool
```
