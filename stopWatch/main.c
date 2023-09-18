/*
 * main.c
 *
 *  Created on: Sep 17, 2023
 *      Author: omart
 */
#include <avr/io.h>
#include "timer.h"
#include "sevSeg.h"
#include "pushB.h"

#define F_CPU 1000000UL

int8_t time[3]={0,0,0};//values for time : time[0]=seconds,time[1]=minutes,time[2]=hours
uint8_t state = 1;//1--> up...0-->down//counting state
uint8_t ON_OFF = 0;//timer on and off state
uint8_t pressFlags[4]={0};//flags to control 4 push buttons with no interrupts
uint8_t time_SEL = 0;//time select to control which time sector is being modified
int main(void)
{
	sevSeg_Init();//time display init
	sevSeg_scnd_Init();//state display init
	initPushB();//control push buttons initiation
	initExtInt();//external interrupts initiation
	t0_Init();//timer 0 initiation for clock control
	t1_Init();//timer 1 initiation for delay function
	displaySeg2(state+1);//display up arrow for an initial state of counting up
	while(1)
	{
		display();//always display time
		if(!ON_OFF)//when pause start checking for our control push buttons
		{
			if(!(PINB & (1<<PB3)))//switch mode (up counting or down counting)
			{
				delayms(3);//for de-bounce
				if(!(PINB & (1<<PB3))&&!pressFlags[0])
				{
					pressFlags[0] = 1;
					state^=1;//switch counting state
					displaySeg2(state+1);//display new state arrow
				}
			}
			else
				pressFlags[0] = 0;


			if (!(PINB & (1 << PB4))) //time select (select which time(seconds,minutes,hours) to be controlled by the increase and decrease buttons)
			{
				delayms(3);
				if (!(PINB & (1 << PB4)) && !pressFlags[1])
				{
					pressFlags[1] = 1;
					time_SEL++;
					if(time_SEL>2)//loop back to seconds when switching of hours
						time_SEL=0;
				}
			}
			else
				pressFlags[1] = 0;


			if (!(PINB & (1 << PB5))) //increase
			{
				delayms(3);
				if (!(PINB & (1 << PB5)) && !pressFlags[2])
				{
					pressFlags[2] = 1;
					time[time_SEL]++;
					if(time_SEL==0&&(time[0]>59))//make sure no overflows
						time[0]=0;
					else if(time_SEL==1&&(time[1]>59))
						time[1]=0;
					else if(time_SEL==2&&(time[2]>99))
						time[2]=0;
				}
			}
			else
				pressFlags[2] = 0;


			if (!(PINB & (1 << PB6))) //decrease
			{
				delayms(3);
				if (!(PINB & (1 << PB6)) && !pressFlags[3])//make sure no overflows
				{
					pressFlags[3] = 1;
					time[time_SEL]--;
					if(time_SEL==0&&time[0]<0)
						time[0]=59;
					else if(time_SEL==1&&time[1]<0)
						time[1]=59;
					else if(time_SEL==2&&time[2]<0)
						time[2]=99;
				}
			}
			else
				pressFlags[3] = 0;
		}
	}
}
