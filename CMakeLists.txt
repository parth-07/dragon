cmake_minimum_required(VERSION 3.16)

project(dragon
        VERSION 0.1.0
        LANGUAGES C CXX)

option(DRAGON_INCLUDE_DOCS "Add targets for building user documentation" OFF)
STRING(CONCAT DRAGON_ENABLE_DOXYGEN_HELP "Add target for building user "
                                         "documentation using doxygen")
option(DRAGON_ENABLE_DOXYGEN ${DRAGON_ENABLE_DOXYGEN_HELP} OFF)
option(DRAGON_BUILD_TESTS "Build test files" OFF)
STRING(CONCAT CATCH_PATH_HELP "Path to Catch2 installation, required when "
                              "catch2 is installed in a non-default path")
option(CATCH_PATH ${CATCH_PATH_HELP})

include_directories(${CMAKE_SOURCE_DIR}/include)

if (DRAGON_INCLUDE_DOCS)
  add_subdirectory(docs)
endif()

if (DRAGON_BUILD_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()