cmake_minimum_required(VERSION 3.4.1)
project("Template")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions")

set(THIRD_PARTY_DIR "../third-party")
set(MAIN_SOURCE_DIR "../src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out)

include_directories(${THIRD_PARTY_DIR}/SDL/include)
include_directories(${THIRD_PARTY_DIR}/glm)
file(GLOB_RECURSE CPP_HEADERS ${MAIN_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE CPP_SOURCES ${MAIN_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE VERT_SHADERS ../assets/shaders/*.vert)
file(GLOB_RECURSE FRAG_SHADERS ../assets/shaders/*.frag)

add_executable(
	Template
	${CPP_HEADERS}
	${CPP_SOURCES}
    ${VERT_SHADERS}
    ${FRAG_SHADERS}
)

set_target_properties(
	Template
	PROPERTIES
	LINK_FLAGS
	"-F../Frameworks -framework SDL2 -framework OpenGL"
)

add_custom_command(
	TARGET Template
	POST_BUILD
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND ./cmake-post-build.sh
)
