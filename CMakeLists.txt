cmake_minimum_required(VERSION 2.8)
if(${AST_STANDLONE})
  include(CMakeLists.standalone)
  return()
endif()

add_clang_executable(ast
  ast.cpp
  )

target_link_libraries(ast
  clangTooling clangBasic clangAST)
