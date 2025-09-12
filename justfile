build_dir := "build"
binary_name := "clay-components"
src_dir := "src"
include_dir := "include"
cmake_toolchain_file := "mingw-w64-toolchain.cmake"
cmake_build_type := "Debug"

default:
	just -l

build:
	mkdir -p {{build_dir}}
	cmake -S . -B {{build_dir}} -DCMAKE_TOOLCHAIN_FILE={{cmake_toolchain_file}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE={{cmake_build_type}}
	cmake --build ./{{build_dir}}

run: build
	./{{build_dir}}/{{binary_name}}.exe

fmt:
    find {{src_dir}} {{include_dir}} -regex '.*\.\(cpp\|hpp\)' | xargs clang-format -i
