add_library(infiniteDouble "")
target_sources(
    infiniteDouble
    PRIVATE
        infiniteDouble.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/infiniteDouble.h
    )

target_include_directories(
    infiniteDouble
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )

