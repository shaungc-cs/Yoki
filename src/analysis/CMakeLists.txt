project(analysis)

find_package(spdlog REQUIRED)

add_library(${PROJECT_NAME} Analysis.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  spdlog::spdlog
  sast_dog_ast_frontend_action
)
