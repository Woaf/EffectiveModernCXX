cmake_minimum_required (VERSION 3.16)

project (InitCapture)

set (HEADERS 
    classes.hpp
)

set (SOURCES
    main.cpp
    classes.cpp
)

add_executable (InitCapture
    ${HEADERS}
    ${SOURCES}
)
