cmake_minimum_required(VERSION 3.15)

set (PROJECT_NAME clay-components)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

set(EXTERNAL_DIR ${CMAKE_CURRENT_LIST_DIR}/../deps)
add_subdirectory(${EXTERNAL_DIR}/raylib ${CMAKE_BINARY_DIR}/raylib)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE EXTERNAL_SRC_FILES external/src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${EXTERNAL_SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    include
	external/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	raylib
)

target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_DESKTOP)
