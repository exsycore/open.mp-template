# GameMode (opem.mp)
Template gamemode c++ using bolt open.mp-gdk and open.mp-sdk

## Usage

Just drop release server.dll or libserver.so (depending on your operating system) in `Components` folder, and run your open.mp server.

## Required Tools

* [CMake 3.19+](https://cmake.org/)
* [Visual Studio 2019+](https://www.visualstudio.com/) (on Windows)
* Clang (on Linux)

## Building on Windows

```bash
mkdir build
cd build
cmake .. -A Win32 -T ClangCL
```

Open Visual Studio and build the solution.

## Building on Linux

```bash
mkdir build
cd build
# May need to configure this line.
export CC=/usr/lib/llvm/13/bin/clang CXX=/usr/lib/llvm/13/bin/clang++
cmake .. -G Ninja -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32 -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
```

Change `Debug` to `Release` for final versions.
