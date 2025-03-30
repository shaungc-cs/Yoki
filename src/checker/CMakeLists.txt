project(checker)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(compliance)
add_subdirectory(core)
add_subdirectory(checker_utils)
