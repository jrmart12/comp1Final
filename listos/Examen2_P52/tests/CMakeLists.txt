cmake_minimum_required (VERSION 2.6)
project (test_interp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)
  
add_executable(test_interp ${PROJECT_SOURCE_DIR}/../spl_ast.cpp
                           test_interp.cpp)

target_compile_options(test_interp PRIVATE -std=c++14)

enable_testing()
add_test(NAME test_interp
         COMMAND test_interp)
