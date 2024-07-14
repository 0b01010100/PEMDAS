cmake_minimum_required(VERSION 3.22)

project(testProbGen LANGUAGES C CXX)

# Set output directories for different target types
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(ProbGen STATIC ProbGen.c)

add_executable(testProbGen main.cpp ProbGen)

target_include_directories(testProbGen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(testProbGen PUBLIC ProbGen)
