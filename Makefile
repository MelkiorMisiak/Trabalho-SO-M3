OBJS = build/start.o build/trap_entry.o build/context.o \
       build/main.o build/task.o build/scheduler.o build/uart.o build/string.o build/memory.o

main:
	riscv64-none-elf-ld -T linker.ld $(OBJS) -o kernel.elf


cmake:
	cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/riscv-toolchain.cmake



