cmake_minimum_required(VERSION 3.16)
project(app)

add_library(someclass SHARED src/SomeClass.cpp)
add_library(func SHARED src/fun.cpp)
add_executable(app app.cpp)

target_include_directories(someclass PUBLIC
${CMAKE_SOURCE_DIR})
target_include_directories(app PUBLIC
${CMAKE_SOURCE_DIR})
target_include_directories(func PUBLIC
${CMAKE_SOURCE_DIR})

target_link_libraries(app
someclass)
target_link_libraries(someclass
func)