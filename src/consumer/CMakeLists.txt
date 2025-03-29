project(sast_dog_ast_consumer)

find_package(nlohmann_json REQUIRED)

add_library(${PROJECT_NAME} SastDogASTConsumer.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  nlohmann_json::nlohmann_json
  sast_dog_ast_visitor
)
