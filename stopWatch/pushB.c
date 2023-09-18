/*
 * pushB.c
 *
 *  Created on: Sep 17, 2023
 *      Author: omart
 */

#include "pushB.h"
void initExtInt(void)
{
	DDRD &= ~((1<<PD2)|(1<<PD3));
	PORTD |= 1<<PD2;
	DDRB &= ~(1<<PB2);
	PORTB |= 1<<PB2;

	SREG |= 1<<7;

	//:INT0 ---> falling edge ---> reset timer
	MCUCR |= 1<<ISC01;
	//:INT1 ---> rising edge ---> pause timer
	MCUCR |= 1<<ISC11 | 1<<ISC10;
	//:INT2 ---> falling edge ---> resume timer
	MCUCSR &= ~(1<<ISC2);

	GICR |= (1<<INT0)|(1<<INT1)|(1<<INT2);
}

void initPushB(void)
{
	DDRB &= ~(0b01111000);
	PORTB |= 0b01111000;
}
uint8_t PB_Press()
{
	if(PINB & (1<<PB3))
		return 1;//switch mode
	if(PINB & (1<<PB4))
		return 2;//time select
	if(PINB & (1<<PB5))
		return 3;//increase
	if(PINB & (1<<PB6))
		return 4;//decrease
	return 0;//no button pressed
}
ISR(INT0_vect)
{
	//reset timer
	TCCR1B &= ~((1<<CS10)|(1<<CS11));
	TCNT1 = 0;
	ON_OFF=0;
	time[0]=0;
	time[1]=0;
	time[2]=0;
}
ISR(INT1_vect)
{
	//:Timer clock stop
	TCCR1B &= ~((1<<CS10)|(1<<CS11));
	ON_OFF=0;
	displaySeg2(0);
}
ISR(INT2_vect)
{
	//:timer clock start
	TCCR1B |= (1<<CS10) | (1<<CS11);
	ON_OFF=1;
	displaySeg2(state+1);
}
