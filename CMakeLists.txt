cmake_minimum_required(VERSION 3.20 )
project(Library_System)

set(CMAKE_CXX_STANDARD 17)

add_executable(Library_System main.cpp book.cpp book.h customer.cpp customer.h library.cpp library.h)
