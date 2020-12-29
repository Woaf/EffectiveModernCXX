cmake_minimum_required (VERSION 3.19)

project (PreferMakeCtor)

set (HEADERS
    classes.hpp
)

set (SOURCES 
    main.cpp
    classes.cpp
)

add_executable (PreferMakeCtor ${SOURCES} ${HEADERS})
