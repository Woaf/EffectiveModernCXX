cmake_minimum_required (VERSION 3.19)

project (Shared_ptrs)

set (HEADERS 
    classes.hpp
)

set (SOURCES
    main.cpp
    classes.cpp
)

add_executable (Shared_ptrs ${HEADERS} ${SOURCES})
