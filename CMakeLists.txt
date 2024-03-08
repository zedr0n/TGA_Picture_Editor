cmake_minimum_required(VERSION 3.28)
project(tgalib)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(extern/pybind11)
pybind11_add_module(tgalib pybind.cpp TGAPicture.cpp Header.cpp Pixel.cpp)
add_executable(text.exe text.cpp TGAPicture.cpp Header.cpp Pixel.cpp)
