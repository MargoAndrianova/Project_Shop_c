cmake_minimum_required(VERSION 3.29)
project(Project_Shop_c C)

set(CMAKE_C_STANDARD 11)

add_executable(Project_Shop_c main.c
        shop.c
        shop.h
        )

add_executable(main main.c shop.c shop.h)
add_executable(test shop_test.c shop.c shop.h)

target_link_libraries(test)