cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)
project ("2.2")
add_executable (CMakeTarget 2.2.cpp bar.h bar.cpp multibar.h multibar.cpp color.h color.cpp)