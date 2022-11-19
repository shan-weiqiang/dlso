cmake_minimum_required(VERSION 3.16)
project(app)

add_library(some SHARED src/SomeClass.cpp)
add_executable(app app.cpp)

target_include_directories(some PUBLIC
${CMAKE_SOURCE_DIR})
target_include_directories(app PUBLIC
${CMAKE_SOURCE_DIR})

target_link_libraries(app
dl)


