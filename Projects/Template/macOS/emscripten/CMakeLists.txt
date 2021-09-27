cmake_minimum_required(VERSION 3.4.1)
project("Template")

set(CMAKE_CXX_FALGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions")

set(THIRD_PARTY_DIR "../third-party")
set(MAIN_SOURCE_DIR "../src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out)

include_directories(${THIRD_PARTY_DIR}/SDL/include)

file(GLOB_RECURSE CPP_HEADERS ${MAIN_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE CPP_SOURCES ${MAIN_SOURCE_DIR}/*.cpp)

add_executable(
	Template
	${CPP_HEADERS}
	${CPP_SOURCES}
)

set_target_properties(
	Template
	PROPERTIES
	LINK_FLAGS
	"-O2 -s USE_SDL=2 -s USE_WEBGL2=1"
)

add_custom_command(
	TARGET Template
	POST_BUILD
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND ./cmake-post-build.sh
)
