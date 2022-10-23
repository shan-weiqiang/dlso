add_library(secondlib SHARED secondlib.cpp)
target_include_directories(secondlib PUBLIC
	${CMAKE_SOURCE_DIR})
