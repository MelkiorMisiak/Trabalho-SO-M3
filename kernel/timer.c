#include "timer.h"

static uint64_t tick_interval = 100000;

static inline void sbi_set_timer(uint64_t time)
{
	register uint64_t a0 asm ("a0") = time;
	register uint64_t a6 asm ("a6") = 0x54494D45; //EID TIME
	register uint64_t a7 asm ("a7") = 0;         

	asm volatile (
	"ecall"
	: "+r" (a0)
	: "r" (a6), "r" (a7)
	: "memory"
	); 
}

void timer_next(void)
{
	uint64_t now;

	asm volatile("csrr %0, time": "=r"(now));
	
	sbi_set_timer(now + tick_interval);
}

void timer_init(uint64_t interval)
{
	if (interval != 0)
		tick_interval = interval;
	timer_next();

	asm volatile("csrs sie, %0" :: "r"(0x20));
	asm volatile("csrs sstatus, %0" :: "r"(0x2));
}
