cmake_minimum_required (VERSION 2.6)
project (test_ast)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14" )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)
  
add_executable(test_ast ${PROJECT_SOURCE_DIR}/../expr_ast.cpp
                        test_ast.cpp)

enable_testing()
add_test(NAME test_ast
         COMMAND test_ast)
