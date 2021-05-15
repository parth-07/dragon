cmake_minimum_required(VERSION 3.16)

project(dragon
        VERSION 1.0.0
        LANGUAGES C CXX)

enable_testing()

find_package(Catch2 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
