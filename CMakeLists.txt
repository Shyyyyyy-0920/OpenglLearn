cmake_minimum_required(VERSION 3.16)
add_definitions(-DDEBUG)
project(OpenGLLearn)

set(CMAKE_CXX_STANDARD 17)

file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})
include_directories(
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/third_party/include
)

link_directories(
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib
)

add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glFramework)

add_executable(OpenGLLearn "main.cpp" "glad.c")

target_link_libraries(OpenGLLearn glfw3.lib wrapper app fw)