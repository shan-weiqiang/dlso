add_library(indep SHARED inde.cpp ${PROJECT_SOURCE_DIR}/greet/src/Greet.cpp)
target_include_directories(indep PUBLIC
	${PROJECT_SOURCE_DIR})
