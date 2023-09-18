/*
 * timer.h
 *
 *  Created on: Sep 17, 2023
 *      Author: omart
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

extern int8_t time[3];
extern uint8_t state;
extern uint8_t ON_OFF;

void t1_Init(void);
void t0_Init(void);
void delayms(uint8_t d);
ISR(TIMER1_COMPA_vect);

#endif /* TIMER_H_ */
