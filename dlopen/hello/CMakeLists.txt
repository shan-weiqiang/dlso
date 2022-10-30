file(GLOB source  src/*.cpp ${PROJECT_SOURCE_DIR}/greet/src/Greet.cpp)
add_library(Hello SHARED ${source})

target_include_directories(Hello PUBLIC
 ${PROJECT_SOURCE_DIR}
 ${CMAKE_SOURCE_DIR})
 # target_link_libraries(Hello PUBLIC
 # test)
