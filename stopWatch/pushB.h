/*
 * pushB.h
 *
 *  Created on: Sep 17, 2023
 *      Author: omart
 */

#ifndef PUSHB_H_
#define PUSHB_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "sevSeg.h"

extern int8_t time[3];
extern uint8_t state;
extern uint8_t ON_OFF;

void initExtInt(void);
void initPushB(void);
uint8_t PB_Press();

ISR(INT0_vect);
ISR(INT1_vect);
ISR(INT2_vect);

#endif /* PUSHB_H_ */
