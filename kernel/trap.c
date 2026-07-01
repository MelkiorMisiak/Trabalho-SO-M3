#include "trap.h"
#include "timer.h"
#include "scheduler.h"
#include "uart.h"

void trap_handler(uint64_t *frame)
{
	uint64_t scause;
	asm volatile("csrr %0, scause" : "=r"(scause));

	if((scause >> 63) && (scause & 0x3F) == 5) {
		timer_next();
		schedule_from_trap(frame);
		return;
	}

	uart_print("Unhandled trap\n");

	while (1)
		;
}
