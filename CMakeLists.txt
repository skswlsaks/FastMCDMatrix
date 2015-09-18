cmake_minimum_required(VERSION 3.2)
project(FastMCD2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES FastMCD.cpp)
add_executable(FastMCD2 ${SOURCE_FILES} Scanner.h Scanner.cpp Cholesky.h Cholesky.cpp Sampling.h Sampling.cpp matrix.h matrix.cpp Calculation.h Calculation.cpp Execution.h Execution.cpp)