/*
 * i2c.h
 *
 * Created: 16. 04. 2018 17:33:26
 *  Author: Marko
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <util/twi.h>

#define SCL_CLOCK 100000L
#define F_CPU 8000000UL
#include <util/delay.h>
	
	void init();
	void write(uint8_t data);
	void stop();
	uint8_t read(uint8_t ack);
	///////////////////////////////
	void startRtc(); //Potreben zato, ker ima start() funkcija znotraj dodatne nastavitve za oled zaslon, ki jih tu ne potrebujem.


#endif /* INCFILE1_H_ */