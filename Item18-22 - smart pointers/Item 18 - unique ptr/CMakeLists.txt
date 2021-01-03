cmake_minimum_required (VERSION 3.16)

project (Unique_pointers)

set (HEADERS
	classes.hpp
)

set (SOURCES
	main.cpp
)

add_executable (Unique_pointers ${HEADERS} ${SOURCES})
