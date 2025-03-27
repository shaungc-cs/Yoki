project(SastDog)

# 查找 LLVM 和 Clang 包
find_package(LLVM REQUIRED CONFIG)

# 打印 LLVM 相关变量以进行调试
message(STATUS "LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM_LIBRARY_DIRS: ${LLVM_LIBRARY_DIRS}")

# 指定源文件
add_executable(${PROJECT_NAME} main.cpp)

# 显式添加库搜索路径和头文件搜索路径
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/third_party/llvm_18/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${LLVM_LIBRARY_DIRS})

# 禁用 ABI Breaking Checks
target_compile_definitions(${PROJECT_NAME} PRIVATE LLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING=1)

target_link_libraries(${PROJECT_NAME}
  clangTooling
  clangASTMatchers
)