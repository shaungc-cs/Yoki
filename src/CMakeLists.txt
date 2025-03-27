project(SastDog)

# 查找 LLVM 和 Clang 包
find_package(LLVM REQUIRED CONFIG)

# 优先使用 vcpkg 安装的包
# list(APPEND CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/x64-linux")

# 打印 LLVM 相关变量以进行调试
message(STATUS "LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM_LIBRARY_DIRS: ${LLVM_LIBRARY_DIRS}")

add_definitions(${LLVM_DEFINITIONS})

# 指定源文件

# 显式添加库搜索路径和头文件搜索路径
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/llvm_18/include)
message(STATUS "CMAKE_CURRENT_LIST_DIR: ${LLVM_LIBRARY_DIRS}")
link_directories(${LLVM_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} main.cpp)
# 禁用 ABI Breaking Checks
# target_compile_definitions(${PROJECT_NAME} PRIVATE LLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING=1)

# 链接库
llvm_map_components_to_libnames(REQ_LLVM_LIBS support core irreader passes)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  ${REQ_LLVM_LIBS}
  clangAST
  clangBasic
  clangAST
  clangDriver
  clangFrontend
  clangSerialization
  clangASTMatchers
  clangTooling
  LLVMSupport
  LLVMCore
  LLVMOption
)
