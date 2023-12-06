# libscrabble

[![Travis CI](https://travis-ci.com/henrikhasell/libscrabble.svg?branch=main)](https://travis-ci.com/github/henrikhasell/libscrabble)

A scrabble library written in C++14 with bindings to C.

# Installing dependencies

On Arch Linux:
```sh
sudo pacman -S gtest
```
On Debian/Ubuntu:
```sh
sudo apt-get install libgtest-dev
```

# Building

You can use `cmake` to build the application:

```sh
mkdir build && cd build
cmake ..
make
```