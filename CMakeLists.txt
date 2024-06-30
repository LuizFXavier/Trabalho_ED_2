cmake_minimum_required(VERSION 3.27)

project(trab2)

add_executable(trab2
    src/hash.c
    src/technical.c
    src/avl.c
    src/cidade.c
    src/menus.c
    src/query.c
    src/main.c)

target_include_directories(trab2 PRIVATE include)