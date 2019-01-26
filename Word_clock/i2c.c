/*
 * i2c.c
 *
 * Created: 16. 04. 2018 17:33:18
 *  Author: Marko
 */ 

/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#include "i2c.h"

//uint16_t RATE = ((F_CPU/SCL_CLOCK)-16)/2;

void init() {
	TWSR = 0;
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
	TWCR = (1<<TWEN);
}


void write(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	
	while(!(TWCR & (1<<TWINT)));
}

void stop() {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	
	
	while(TWCR & (1<<TWSTO));
}


//////////////////////////////////////////////////////////////////////////////////////////


void startRtc() {
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	//int i = TWSR & 0xF8;
	//if(i == 0x08)
	//{
		//PORTB |= (1<<PORTB6);
	//}

	while((TWCR & (1<<TWINT)) == 0);
}

uint8_t read(uint8_t ack)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(ack<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}
