build_dir := "build"
binary_name := "clay-components"
src_dir := "src"
include_dir := "include"
cmake_toolchain_file := "mingw-w64-toolchain.cmake"
cmake_build_type := "Debug"

default:
	just -l

build:
	mkdir -p {{build_dir}}/windows
	cmake -S . -B {{build_dir}}/windows -DCMAKE_TOOLCHAIN_FILE={{cmake_toolchain_file}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE={{cmake_build_type}} -DCMAKE_SYSTEM_NAME=Windows
	cmake --build ./{{build_dir}}/windows
	cp {{build_dir}}/windows/compile_commands.json {{build_dir}}/compile_commands.json

run: build
	wine ./{{build_dir}}/windows/{{binary_name}}.exe

fmt:
    find {{src_dir}} {{include_dir}} -regex '.*\.\(cpp\|hpp\)' | xargs clang-format -i
