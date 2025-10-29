#include "delay.h"
void delay_us(u32 us)
{
	us*=12;
	while(us--);
}
void delay_ms(u32 ms)
{
	ms*=12000;
	while(ms--);
}
void delay_s(u32 s)
{
	s*=12000000;
	while(--s);
}
