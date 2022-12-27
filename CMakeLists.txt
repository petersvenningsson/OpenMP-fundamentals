project(openMP)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "-fopenmp -O0 -g3")
set(CMAKE_C_FLAGS "-fopenmp -O0 -g3")

include_directories(include)

add_executable("hello" "src/hello.c")
add_executable("linked" "src/linked.c")
add_executable("matmul_rec" "src/matmul_recur.cpp")
add_executable("pi" "src/pi.c")
add_executable("prod_cons" "src/prod_cons.c")
add_executable("mandel" "src/mandel.c")
