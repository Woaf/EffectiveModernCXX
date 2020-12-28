cmake_minimum_required (VERSION 3.19)

project (Weak_Pointers)

set (HEADERS 
    classes.hpp
)

set (SOURCES
    classes.cpp
    main.cpp
)

add_executable (Weak_Pointers ${HEADERS} ${SOURCES})
