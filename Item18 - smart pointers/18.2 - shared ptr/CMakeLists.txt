cmake_minimum_required (VERSION 3.18)

project (Shared_ptrs)

set (HEADERS 
    classes.hpp
)

set (SOURCES
    main.cpp
)

add_executable (Shared_ptrs ${HEADERS} ${SOURCES})
