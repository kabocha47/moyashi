#include "iodefine.h"
#include "led.h"

void InitLED(void)
{
	IO.PDR8.BIT.B1 = 1;
	IO.PDR8.BIT.B2 = 1;
	IO.PCR8 = 0x46;
}

void LED1_ON(void)
{
	IO.PDR8.BIT.B1 = 0;
}

void LED1_OFF(void)
{
	IO.PDR8.BIT.B1 = 1;
}

void LED2_ON(void)
{
	IO.PDR8.BIT.B2 = 0;
}

void LED2_OFF(void)
{
	IO.PDR8.BIT.B2 = 1;
}

