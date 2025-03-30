project(SastDog)

# 优先使用 vcpkg 安装的包
list(APPEND CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/x64-linux")

# 查找 LLVM 和 Clang 包
find_package(LLVM REQUIRED CONFIG)

# 打印 LLVM 相关变量以进行调试
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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -w")

set (clang_paths
 ${LLVM_INSTALL_PREFIX}
 ${LLVM_INSTALL_PREFIX}/lib/cmake
 ${LLVM_INSTALL_PREFIX}/lib/cmake/llvm
 ${LLVM_INSTALL_PREFIX}/lib/cmake/clang
 ${LLVM_INSTALL_PREFIX}/share/clang/cmake
 ${LLVM_INSTALL_PREFIX}/share/llvm/cmake
)
find_package(Clang REQUIRED CONFIG PATHS "${clang_paths}")

find_package(spdlog REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
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
  config
  utils
  analysis
  sast_dog_ast_frontend_action
)

add_subdirectory(config)
add_subdirectory(utils)
# add_subdirectory(thread_pool)
add_subdirectory(analysis)
# add_subdirectory(rules)
add_subdirectory(visitor)
add_subdirectory(frontend_action)
add_subdirectory(consumer)
add_subdirectory(common)
add_subdirectory(checker_manager)
add_subdirectory(checker)
