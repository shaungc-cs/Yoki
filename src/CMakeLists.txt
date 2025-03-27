project(SastDog)

# 优先使用 vcpkg 安装的包
list(APPEND CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/x64-linux")

# 查找 LLVM 和 Clang 包
find_package(LLVM REQUIRED CONFIG)

# 打印 LLVM 相关变量以进行调试
message(STATUS "LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM_LIBRARY_DIRS: ${LLVM_LIBRARY_DIRS}")

message(STATUS "Found LLVM: " ${LLVM_FOUND})
message(STATUS "LLVM version: " ${LLVM_VERSION})
message(STATUS "LLVM include directory: " ${LLVM_INCLUDE_DIRS})
message(STATUS "LLVM library directory: " ${LLVM_LIBRARY_DIRS})
message(STATUS "LLVM install path: " ${LLVM_INSTALL_PREFIX})
include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})

link_directories(${LLVM_LIBRARY_DIRS})

# 显式添加库搜索路径和头文件搜索路径
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/third_party/llvm_18/include)

set (search_paths
 ${LLVM_INSTALL_PREFIX}
 ${LLVM_INSTALL_PREFIX}/lib/cmake
 ${LLVM_INSTALL_PREFIX}/lib/cmake/llvm
 ${LLVM_INSTALL_PREFIX}/lib/cmake/clang
 ${LLVM_INSTALL_PREFIX}/share/clang/cmake
 ${LLVM_INSTALL_PREFIX}/share/llvm/cmake
)
# find_package(LLVM REQUIRED CONFIG
#  PATHS ${search_paths}
#  NO_DEFAULT_PATH)
# Solution 2:
find_package(Clang REQUIRED CONFIG
    PATHS "${search_paths}")


    # Set runtime bin/lib output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

add_executable(${PROJECT_NAME} main.cpp)

# 链接库
llvm_map_components_to_libnames(REQ_LLVM_LIBS support core irreader passes)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  ${REQ_LLVM_LIBS}
  clangTooling
  clangFrontend
  clangAST
  clangBasic
  clangDriver
  clangLex
  clangParse
  clangSema
  clangEdit
  clangRewrite
  clangAnalysis
  clangSerialization
  clangStaticAnalyzerCore
  clangStaticAnalyzerFrontend
)
