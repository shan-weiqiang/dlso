add_executable(app src/app.cpp ${PROJECT_SOURCE_DIR}/greet/src/Greet.cpp)
target_include_directories(app PUBLIC
    ${PROJECT_SOURCE_DIR}
    )
target_link_libraries(app PUBLIC
    dl
    test
    Hello)
