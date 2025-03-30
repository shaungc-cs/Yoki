project(checker_manager)

find_package(nlohmann_json REQUIRED)

add_library(${PROJECT_NAME} CheckerManager.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json
helper
compliance
MISRA_CPP2023_Rule_9_6_1
)

add_subdirectory(helper)
