file(GLOB_RECURSE SOURCES "*.hpp" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES})
