cmake_minimum_required(VERSION 3.20)
project(sast_dog VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# 检查 VCPKG_ROOT 是否设置
if(NOT DEFINED ENV{VCPKG_ROOT})
    message(FATAL_ERROR "VCPKG_ROOT environment variable is not set. Please set it to the path where vcpkg is installed.")
else()
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
endif()

# 配置 CMake 使用 Vcpkg 的 toolchain 查找 Vcpkg 依赖包
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# 优先使用 vcpkg 安装的包
list(APPEND CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/x64-linux")

# 查找 LLVM 和 Clang 包
find_package(LLVM REQUIRED CONFIG)

# 打印 LLVM 相关变量以进行调试
message(STATUS "LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM_LIBRARY_DIRS: ${LLVM_LIBRARY_DIRS}")

# 指定源文件
add_executable(${PROJECT_NAME} src/main.cpp)

# 显式添加库搜索路径和头文件搜索路径
target_link_directories(${PROJECT_NAME} PRIVATE ${LLVM_LIBRARY_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${LLVM_INCLUDE_DIRS})

# 禁用 ABI Breaking Checks
target_compile_definitions(${PROJECT_NAME} PRIVATE LLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING=1)


target_link_libraries(${PROJECT_NAME}
  clangTooling
  clangASTMatchers
)
