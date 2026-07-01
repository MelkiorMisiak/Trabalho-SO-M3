#include "scheduler.h"
#include "task.h"

extern void context_switch(void*, void*);

static int current = 0;

/* Round-Robin padrão */

static int round_robin(void)
{
    return (current + 1) % task_count;
}

/* Algoritmo atual */

static sched_algo_t current_algo = round_robin;

void scheduler_set_algorithm(sched_algo_t algo)
{
	if (algo)
		current_algo = algo;
}

/* Yield */

void yield(void)
{
	int prev = current;
	int next = current_algo();

	current = next;

	context_switch(tasks[prev].regs, tasks[next].regs);
}
 
/* Início */

void scheduler_start(void)
{
	if (task_count == 0)
		return;

	tasks[0].entry();
}

void scheduler_from_trap(uint64_t *frame)
{
	int prev = current;
	int next = current_algo();

	for(uint32_t i = 0; i < 32; i++)
		tasks[prev].regs[i] = frame[i];
	
	asm volatile("csrr %0, sepc" :: "r"(tasks[prev].sepc));

        current = next;

	for(uint32_t i = 0; i < 32; i++)
		frame[i] = tasks[next].regs[i];

	asm volatile("csrw sepc, %0" :: "r"(tasks[next].sepc));
}


