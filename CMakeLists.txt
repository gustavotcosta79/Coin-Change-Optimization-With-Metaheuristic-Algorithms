cmake_minimum_required(VERSION 3.26)
project(TP2_IIA C)

set(CMAKE_C_STANDARD 11)

add_executable(TP2_IIA main.c
        utils.c
        funcao.c
        funcao.h
        algoritmo.c
        algoritmo.h
        utils.h)
