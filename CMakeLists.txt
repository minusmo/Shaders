cmake_minimum_required(VERSION 3.23)
project(shaders CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE ${CMAKE_SOURCE_DIR})

# include glad into this library
# 1. include "include" directory itself
include_directories(glad/include)
# 2. Generate list of files matches with the pattern
file(GLOB BUTTERFLIES_SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR} *.c glad/src/gl.c)
## 3. Add glad library definition code.
#add_library(glad INTERFACE glad/src/glad.c)
## 4. Link the library directory to the libary or executable.
#target_link_libraries(${PROJECT_NAME} INTERFACE glad)