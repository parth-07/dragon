find_package(Catch2 REQUIRED PATHS ${CATCH_PATH})
add_library(main OBJECT main.cpp)
include(Catch)

set(items algos core ds graph maths sorting string tree)

foreach(item IN LISTS items)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${item})
  file(GLOB test_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}/*.cpp")
  foreach (test_file IN LISTS test_files)
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} main Catch2::Catch2)
    catch_discover_tests(${test_name})
  endforeach()
endforeach()




