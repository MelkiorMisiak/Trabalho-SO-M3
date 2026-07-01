cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(so-m3 VERSION 1.0 LANGUAGES C ASM)

set(RISCV_FLAGS "-march=rv64gc -mabi=lp64 -mcmodel=medany -msmall-data-limit=0 -ffreestanding -nostdlib -nostartfiles -fno-stack-protector -Wall -Iinclude")


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${RISCV_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${RISCV_FLAGS} -x assembler-with-cpp")


# file(GLOB SOURCES "src/*.c")

add_library(main OBJECT
  kernel/context.S
  kernel/main.c
  kernel/memory.c
  kernel/scheduler.c
  kernel/string.c 
  kernel/syscall.c
  kernel/task.c
  kernel/timer.c
  kernel/trap.c
  kernel/uart.c
  kernel/user.S

)

target_include_directories(main
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)


