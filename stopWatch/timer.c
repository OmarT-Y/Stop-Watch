/*
 * timer.c
 *
 *  Created on: Sep 17, 2023
 *      Author: omart
 */

#include "timer.h"
uint8_t o=0;

void t1_Init(void)
{
	TCCR1A |= 1<<FOC1A;
	TCCR1B |= 1<<WGM12;
	OCR1A = 15625;
	TIMSK |= 1<< OCIE1A;
	TCNT1 = 0;
}

ISR(TIMER1_COMPA_vect)
{
	if (state == 1)
	{
		time[0]++;
		if (time[0] > 59)
		{
			time[0] = 0;
			time[1]++;
		}
		if (time[1] > 59)
		{
			time[1] = 0;
			time[2]++;
		}
		if (time[2] > 99)
		{
			time[0] = 0;
			time[1] = 0;
			time[2] = 0;
		}
	}
	else
	{
		time[0]--;
		if(time[0]<0)
		{
			time[0]=59;
			time[1]--;
		}
		if(time[1]<0)
		{
			time[1]=59;
			time[2]--;
		}
		if(time[2]<0)
		{
			time[0] = 0;
			time[1] = 0;
			time[2] = 0;
		}
	}
}

void t0_Init(void)
{
	TCCR0 |= (1<<FOC0) | (1<<WGM01) | (1<<CS01);
	OCR0 = 125;
	TCNT0 = 0;
}

void delayms(uint8_t d)
{
	for(o=0;o<d;o++)
	{
		TCNT0 = 0;
		TIFR |= 1<<OCF0;
		while(!(TIFR & 1<<OCF0));
	}
}
