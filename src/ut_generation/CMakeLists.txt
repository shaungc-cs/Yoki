cmake_minimum_required(VERSION 3.16)

# UT Generation 库
set(PROJECT_NAME ut_generation)

# 创建一个空的库，为将来的UT生成功能预留
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
