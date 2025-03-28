project(config_node)

add_library(config_node ConfigNode.cpp)

target_include_directories(config_node PUBLIC ${CMAKE_CURRENT_LIST_DIR})