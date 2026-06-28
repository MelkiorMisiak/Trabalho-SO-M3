cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(so-m3 VERSION 1.0 LANGUAGES C ASM)

# file(GLOB SOURCES "src/*.c")

add_executable(main 
  src/main.c
  src/lib.c
)

target_include_directories(main
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)


