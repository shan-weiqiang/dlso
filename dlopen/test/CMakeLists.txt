add_library(test SHARED test.cpp ${PROJECT_SOURCE_DIR}/greet/src/Greet.cpp)
target_include_directories(test PUBLIC
    ${PROJECT_SOURCE_DIR})

