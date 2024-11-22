# GBDK-CMake-Template

## About

This is a simple template to make GameBoy/GameBoy color games using the GBDK.

Btw this template is on the CC0 license so do whatever you want with it.

[![License: CC0-1.0](https://img.shields.io/badge/License-CC0_1.0-lightgrey.svg)](http://creativecommons.org/publicdomain/zero/1.0/)

## How to Build?

Just do these commands if it's the first time building it:


```
mkdir build
cd build
cmake ..
make
```

Then if you want to rebuild redo the `make` command **in the `build` folder**.

> [!IMPORTANT]  
> If you've edited `CMakeLists.txt`, is recommended to delete build folder and redo the first steps!

## How to update/change GBDK version?

Edit this line on the `CMakeLists.txt`:

```cmake
9 | set(GBDK_VERSION "4.3.0")
```

> [!IMPORTANT]
> If the target version is less or equal than 4.0, then put a 'v' before the version number.
>
> e.g for GBDK 3.1.1:
> ```cmake
> set(GBDK_VERSION "v3.1.1")
> ```

# Recommended actions

If you want to clean you build files. I recommend to use the command `make clean_all` instead of the classic `make clean`.
