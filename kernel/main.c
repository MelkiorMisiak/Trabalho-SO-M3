#include "task.h"
#include "scheduler.h"
#include "memory.h"
#include "uart.h"
#include "timer.h"
#include "trap.h"
#include "fs.h"
#include "string.h"

extern void uart_print(const char*);
extern void trap_entry(void);

/* Tasks */

void task1(void)
{
	while(1) 
		uart_print("Task 1 running\n");
}
void task2(void)
{
	while(1) 
		uart_print("Task 2 running\n");
}


/* Kernel */

void kernel_main()
{
	uart_print("\n=== Kernel Booted ===\n");

	fs_init();
	fs_create("notas.txt");
	int fd = fs_open("notas.txt");

	fs_write(fd,"Bem-vindo ao SimpleFAT", 22); 
	char read_buffer[64] = {0}; 
	fs_read(fd, read_buffer, 22);
	uart_print(read_buffer);

	fd = fs_close(fd);

	while (1) 
		;
}
