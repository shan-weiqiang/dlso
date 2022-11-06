cmake_minimum_required(VERSION 3.16)
project(app)
get_filename_component(DATASOURCE ${CMAKE_SOURCE_DIR} DIRECTORY BASE_DIR)

add_library(first SHARED first.cpp)
add_library(second SHARED second.cpp)
add_executable(app app.cpp)
add_library(dependent SHARED dependent.cpp)

target_include_directories(first PUBLIC ${DATASOURCE})
target_include_directories(second PUBLIC ${DATASOURCE})
target_include_directories(app PUBLIC ${DATASOURCE})
target_include_directories(dependent PUBLIC ${DATASOURCE})
target_link_libraries(app
dl
dependent)

# -rdynamic/-export-dynamic compile and link flag will export all symbols in app to .dymsym
# target_compile_options(app PUBLIC 
# -rdynamic)
# target_link_options(app PUBLIC
# -export-dynamic)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)


