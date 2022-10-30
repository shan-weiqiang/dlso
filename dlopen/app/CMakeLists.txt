add_executable(app src/app.cpp ${PROJECT_SOURCE_DIR}/greet/src/Greet.cpp)
add_executable(halfapp src/halfapp.cpp)
target_include_directories(app PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    )
    target_include_directories(halfapp PUBLIC
	    ${PROJECT_SOURCE_DIR})
    # @attention: in following shared libs, Hello has extern ex_sample, indep has ex_sample; if app is dependent of Hello, apps is chained to be dependent of indep; if no indep, there will be undefined symbols for ex_sample, because in Hello, program use ex_sample.
target_link_libraries(app PUBLIC
	# here symbols in app with extern keywords will search in appearance order in following libs
    test
    Hello
    indep
    )
target_link_libraries(halfapp PUBLIC
	half)
