#ifndef TASK_H
#define TASK_H 1

#include <stdint.h>

#define MAX_TASKS 8
#define DEFAULT_STACK_SIZE 2048

struct TCB
{
	uint64_t regs[31]; // x1-x31 (x0 é zero)
	uint64_t sepc;

	void (*entry)(void);

	uint8_t *stack;
	uint64_t stack_size;

	int priority;
	int state;

};

extern struct TCB tasks[MAX_TASKS];
extern int task_count;

void xTaskCreate(void (*task)(void), uint32_t stack_size, int priority);

#endif
