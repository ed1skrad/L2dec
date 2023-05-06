cmake_minimum_required(VERSION 3.24)
project(dec C)

set(CMAKE_C_STANDARD 90)

add_executable(dec main.c Utilits.c openFile.c File.c Decompressing.c)
