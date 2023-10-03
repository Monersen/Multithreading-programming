﻿cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)
project ("course_p")
add_executable (CMakeTarget course_p.cpp q.hpp threadsafe_q.hpp thread_pool.hpp)