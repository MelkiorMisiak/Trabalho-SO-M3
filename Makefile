CROSS = riscv64-none-elf-

CFLAGS = -march=rv64gc -mabi=lp64 \
         -mcmodel=medany \
         -msmall-data-limit=0 \
         -ffreestanding \
         -nostdlib -nostartfiles \
         -fno-stack-protector \
         -Wall -Iinclude

OBJS = build/start.o build/trap_entry.o build/context.o \
       build/main.o build/task.o build/scheduler.o build/uart.o build/string.o build/memory.o \
			 build/trap.o build/timer.o

all:
	$(CROSS)gcc $(CFLAGS) -c boot/start.S -o build/start.o
	$(CROSS)gcc $(CFLAGS) -c boot/trap_entry.S -o build/trap_entry.o
	$(CROSS)gcc $(CFLAGS) -c kernel/context.S -o build/context.o

	$(CROSS)gcc $(CFLAGS) -c kernel/main.c -o build/main.o
	$(CROSS)gcc $(CFLAGS) -c kernel/task.c -o build/task.o
	$(CROSS)gcc $(CFLAGS) -c kernel/scheduler.c -o build/scheduler.o
	$(CROSS)gcc $(CFLAGS) -c kernel/uart.c -o build/uart.o
	$(CROSS)gcc $(CFLAGS) -c kernel/string.c -o build/string.o
	$(CROSS)gcc $(CFLAGS) -c kernel/memory.c -o build/memory.o

	$(CROSS)gcc $(CFLAGS) -c kernel/trap.c -o build/trap.o
	$(CROSS)gcc $(CFLAGS) -c kernel/timer.c -o build/timer.o

	$(CROSS)ld -T linker.ld $(OBJS) -o kernel.elf

cmake:
	cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/riscv-toolchain.cmake

run:
	qemu-system-riscv64 \
		-machine virt \
		-m 128M \
		-nographic \
		-bios default \
		-kernel kernel.elf

clean:
	rm -rf build/*
	make cmake -B
