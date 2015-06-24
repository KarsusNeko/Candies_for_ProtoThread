#include "timer.h"

void timer_set(timer_t* t, unsigned long timeout)
{
	t->start_tick	= ticks;
	t->timeout_tick	= timeout;
}

int timer_expired(timer_t* t)
{
	return (ticks > t->start_tick + t->timeout_tick);
}
