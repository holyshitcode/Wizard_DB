cmake_minimum_required(VERSION 3.29)
project(wizard_db C)

set(CMAKE_C_STANDARD 99)

add_executable(wizard_db main.c
        linked_list.c
        key.c
        chain.c
        data.c
        database.c
        index_tree.c)
