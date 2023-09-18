/*
 * sevSeg.c
 *
 *  Created on: Sep 17, 2023
 *      Author: omart
 */

#include "sevSeg.h"

uint8_t sevSeg_VAL[6]={0};
uint8_t i =0;

void sevSeg_Init(void)
{
	SEG_CTRL_DDR |= 0b00111111;
	SEG_CTRL_PORT |= 0b00111111;
	SEG_DDR |= 15;
}

void sevSeg_scnd_Init(void)
{
	SEG2_DDR |= (1<<SEG2_P)|(1<<SEG2_M) | (1<<SEG2_K)|(1<<SEG2_H);
	SEG2_PORT &= ~((1<<SEG2_P)|(1<<SEG2_M) | (1<<SEG2_K)|(1<<SEG2_H));
}

void parseAll(void)
{
	sevSeg_VAL[0]=time[0]%10;
	sevSeg_VAL[1]=time[0]/10;
	sevSeg_VAL[2]=time[1]%10;
	sevSeg_VAL[3]=time[1]/10;
	sevSeg_VAL[4]=time[2]%10;
	sevSeg_VAL[5]=time[2]/10;
}

void display(void)
{
	parseAll();
	for(i=0;i<6;i++)
	{
		SEG_CTRL_PORT |= 1<<i;
		SEG_PORT = (SEG_PORT&0xF0) | (sevSeg_VAL[i]&0x0F);
		delayms(3);
		SEG_CTRL_PORT &= ~(1<<i);
	}
}

void displaySeg2(uint8_t tri)
{
	switch(tri)
	{
	case 0:
		SEG2_PORT |= (1<<SEG2_P)|(1<<SEG2_M) | (1<<SEG2_K)|(1<<SEG2_H);
		break;
	case 2:
		SEG2_PORT |=(1<<SEG2_M) | (1<<SEG2_K);
		SEG2_PORT &= ~((1<<SEG2_P)|(1<<SEG2_H));
		break;
	case 1:
		SEG2_PORT |=(1<<SEG2_P) | (1<<SEG2_H);
		SEG2_PORT &= ~((1<<SEG2_M)|(1<<SEG2_K));
		break;
	}
}
