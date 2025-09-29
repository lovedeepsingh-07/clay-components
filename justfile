BUILD_DIR := "build"
BINARY_NAME := "clay-components"
PUBLIC_DIR := "public"
CMAKE_TOOLCHAIN_FILE := "mingw-w64-toolchain.cmake"
BUILD_TYPE := "Release"
export EM_CACHE := env_var('HOME') + '/.cache/emscripten'

default:
	just -l

init:
	nix run .#setup

build:
	mkdir -p {{BUILD_DIR}}/windows
	cmake -S . -B {{BUILD_DIR}}/windows -DCMAKE_TOOLCHAIN_FILE={{CMAKE_TOOLCHAIN_FILE}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_TYPE={{BUILD_TYPE}} -DCMAKE_SYSTEM_NAME=Windows
	cmake --build ./{{BUILD_DIR}}/windows
	cp {{BUILD_DIR}}/windows/compile_commands.json {{BUILD_DIR}}/compile_commands.json

run: build
	{{BUILD_DIR}}/windows/{{BINARY_NAME}}.exe

build-web:
	mkdir -p {{BUILD_DIR}}/web
	emcmake cmake -S . -B {{BUILD_DIR}}/web -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_TYPE={{BUILD_TYPE}}
	cmake --build ./{{BUILD_DIR}}/web
	cp {{BUILD_DIR}}/web/compile_commands.json {{BUILD_DIR}}/compile_commands.json
	mkdir -p {{BUILD_DIR}}/public
	cp {{BUILD_DIR}}/web/{{BINARY_NAME}}.* {{BUILD_DIR}}/public/
	cp {{PUBLIC_DIR}}/index.html {{BUILD_DIR}}/public/
	cp {{PUBLIC_DIR}}/style.css {{BUILD_DIR}}/public/
	cp {{PUBLIC_DIR}}/script.js {{BUILD_DIR}}/public/
serve: build-web
	live-server {{BUILD_DIR}}/public --port=3000

fmt:
    find src include -regex '.*\.\(cpp\|hpp\)' | xargs clang-format -i
