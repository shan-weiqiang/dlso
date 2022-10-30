add_library(half SHARED halfso.cpp)
add_library(definition SHARED definition.cpp)
target_include_directories(half PUBLIC
	${PROJECT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR})
