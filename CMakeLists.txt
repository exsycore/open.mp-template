cmake_minimum_required(VERSION 3.20)
project(server LANGUAGES C CXX VERSION 0.0.1)

add_subdirectory(lib/open.mp-sdk)
add_subdirectory(lib/open.mp-gdk)

add_subdirectory(gamemode)

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output
)

set_target_properties(omp-gdk PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OMP-SDK
    omp-gdk
)