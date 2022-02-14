cmake_minimum_required(VERSION 3.20)
project(Assignment1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment1 main.cpp)
target_compile_options(Assignment1 PRIVATE -Wall -Werror -Wextra -pedantic)
