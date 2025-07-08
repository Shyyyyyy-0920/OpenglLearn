cmake_minimum_required(VERSION 3.16)
project(OpenGLLearn)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/third_party/include
)

link_directories(
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib
)

add_executable(OpenGLLearn "main.cpp" "glad.c")

target_link_libraries(OpenGLLearn glfw3.lib)