cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fno-rtti -Wall")

# A convenience variable:
set(LLVM_SOURCE_ROOT "${CMAKE_CURRENT_BINARY_DIR}/../source.git" CACHE PATH "Root of LLVM source.")
set(LLVM_BUILD_ROOT "${CMAKE_CURRENT_BINARY_DIR}/../build.git" CACHE PATH "Root of LLVM install.")

# A bit of a sanity check:
if( NOT EXISTS ${LLVM_BUILD_ROOT}/include/llvm )
	message(FATAL_ERROR "LLVM_BUILD_ROOT (${LLVM_BUILD_ROOT}) is not a valid LLVM install")
endif()

# We incorporate the CMake features provided by LLVM:
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_BUILD_ROOT}/share/llvm/cmake")
include(LLVMConfig)

set(LLVM_INCLUDE_DIRS "${LLVM_SOURCE_ROOT}/include" "${LLVM_BUILD_ROOT}/include")
set(CLANG_INCLUDE_DIRS "${LLVM_SOURCE_ROOT}/tools/clang/include" "${LLVM_BUILD_ROOT}/tools/clang/include")
set(LLVM_LIBRARY_DIRS "${LLVM_BUILD_ROOT}/lib")

# Now set the header and library paths:
include_directories( ${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
link_directories( ${LLVM_LIBRARY_DIRS} )
add_definitions( ${LLVM_DEFINITIONS} )

llvm_map_components_to_libraries(REQ_LLVM_LIBRARIES core mc)
#set(REQ_CLANG_LIBRARIES clangFrontend clangSema clangParse clangRewrite clangAST clangLex clangBasic)
set(REQ_CLANG_LIBRARIES clang clangTooling)

add_executable(ast ast.cpp)
target_link_libraries(ast ${REQ_LLVM_LIBRARIES} ${REQ_CLANG_LIBRARIES} profiler)

add_subdirectory(test)
