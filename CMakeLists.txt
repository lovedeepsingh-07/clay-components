cmake_minimum_required(VERSION 3.15)

set (PROJECT_NAME clay-components)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXTERNAL_DIR deps)
add_subdirectory(${EXTERNAL_DIR}/raylib)

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

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
	set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".js")
	target_link_options(${PROJECT_NAME} PRIVATE
        "-sUSE_GLFW=3"
        "-sASYNCIFY"
        "-sFORCE_FILESYSTEM"
		"-sEXPORTED_RUNTIME_METHODS=['cwrap']"
        "-sMODULARIZE"
        "-sEXPORT_ES6"
        "-sENVIRONMENT=web"
		"-sALLOW_MEMORY_GROWTH=1"
		"-sSTACK_SIZE=1mb"
		"--preload-file=${CMAKE_SOURCE_DIR}/assets@/assets"
    )
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
	target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_DESKTOP)
endif()
