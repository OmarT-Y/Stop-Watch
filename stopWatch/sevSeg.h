/*
 * sevSeg.h
 *
 *  Created on: Sep 17, 2023
 *      Author: omart
 */

#ifndef SEVSEG_H_
#define SEVSEG_H_

#include <avr/io.h>
#include "timer.h"

extern int8_t time[3];
extern uint8_t state;
extern uint8_t ON_OFF;

#define SEG_CTRL_DDR DDRA
#define SEG_CTRL_PORT PORTA


#define SEG_DDR DDRC
#define SEG_PORT PORTC

#define SEG2_DDR DDRD
#define SEG2_PORT PORTD
#define SEG2_P PD4
#define SEG2_H PD5
#define SEG2_K PD6
#define SEG2_M PD7

void parseAll(void);
void sevSeg_Init(void);
void display(void);

void sevSeg_scnd_Init(void);
void displaySeg2(uint8_t tri);

#endif /* SEVSEG_H_ */
