cmake_minimum_required(VERSION 3.16)

project(dragon
        VERSION 0.1.0
        LANGUAGES C CXX)

option(DRAGON_BUILD_TESTS "Build test files" OFF)
STRING(CONCAT CATCH_PATH_HELP "Path to Catch2 installation, required when "
                              "catch2 is installed in a non-default path")
option(CATCH_PATH ${CATCH_PATH_HELP})

include_directories(${CMAKE_SOURCE_DIR}/include)

if (DRAGON_BUILD_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()