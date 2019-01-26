/*
 * display.h
 *
 * Created: 16. 04. 2018 17:18:30
 *  Author: Marko
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

//Makroji za nadziranje shift registrov
#define strobe1 PORTD5
#define data1   PORTD6
#define clock1 PORTD7
#define output_en1 PORTB0

#define strobe2 PORTD2
#define data2   PORTD1
#define clock2 PORTD0
#define output_en2 PORTD3

#define strobe3 PORTC2
#define data3   PORTC1
#define clock3 PORTC0
#define output_en3 PORTC3

//bitshift1
#define ena1		7
#define dva1		6
#define tri1		5
#define stiri1		4
#define pet1		3
#define sest1		2
#define sedem1		1

//bitshift2
#define osem2		7
#define devet2		6
#define deset2		5
#define enajst2		4
#define dvanajst2	3
#define ura2		2
#define je2			1

//bitshift3
#define cez3		7
#define do3			6
#define pol3		5
#define minut3		4
#define petm3		3
#define desetm3		2
#define petanjstm3	1

extern int bit1;
extern int bit2;
extern int bit3;

void bitshift1(int bit);
void bitshift2(int bit);
void bitshift3(int bit);

void izberiUre(uint8_t ure);
void izberiMinuteinUre(uint8_t cas_ure, uint8_t cas_minute);



#endif /* DISPLAY_H_ */