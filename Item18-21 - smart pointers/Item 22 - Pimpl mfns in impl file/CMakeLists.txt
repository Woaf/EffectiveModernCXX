cmake_minimum_required (VERSION 3.19)

project (Pimpl) 

set (HEADERS 
    classes.hpp
    person.hpp
)

set (SOURCES
    main.cpp
    classes.cpp
    person.cpp
)

add_executable (Pimpl ${HEADERS} ${SOURCES})
