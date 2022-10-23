add_library(somelib SHARED somelib.cpp)
target_include_directories(somelib PUBLIC
	${CMAKE_SOURCE_DIR})
