/*
 * display.c
 *
 * Created: 16. 04. 2018 17:19:06
 *  Author: Marko
 */ 
#include "display.h"

//globalni biti za bitshift registre, njihova vrednost bo doloèala katera beseda bo prižgana
int bit1 = 0b00000000;
int bit2 = 0b00000110;
int bit3 = 0b00000000;

void bitshift1(int bit)
{
	PORTD &= ~(1<<strobe1); //strobe linija je ugasnjena da se izhod ne updejta
	PORTB |= 1<<output_en1;
	uint8_t temp;		
	int delay = 1;
	
	for(int i = 0; i < 16; i++)
	{
		if(i % 2 == 0)
		{
			temp = (bit & 1);
			
			if(temp)
			PORTD |= 1<<data1;
			else
			PORTD &= ~(1<<data1);
			
			bit = bit>>1;
		}

		if(i != 0)
		{
			PORTD ^= 1<<clock1;
			_delay_ms(delay);
		}
	}
	
	PORTD |= 1<<strobe1;	//vrednosti se updejtajo


	PORTD ^= 1<<clock1;		//konèni vrednosti za clock in data linijo
	PORTD &= ~(1<<data1);
	
	PORTB |= 1<<output_en1;
}

void bitshift2(int bit)
{
	PORTD &= ~(1<<strobe2); //Strobe linija je ugasnjena da se izhod ne updejta
	PORTD |= 1<<output_en2;
	uint8_t temp;		
	int delay = 1;
	
	for(int i = 0; i < 16; i++)
	{
		if(i % 2 == 0)
		{
			temp = (bit & 1);
			
			if(temp)
			PORTD |= 1<<data2;
			else
			PORTD &= ~(1<<data2);
			
			bit = bit>>1;
		}

		if(i != 0)
		{
			PORTD ^= 1<<clock2;
			_delay_ms(delay);
		}
	}
	
	//PORTD |= 1<<strobe2;	//Vrednosti se updejtajo


	PORTD ^= 1<<clock2;		//konèni vrednosti za clock in data linijo
	PORTD &= ~(1<<data2);
	
	PORTD |= 1<<output_en2;
}

void bitshift3(int bit)
{
	PORTC &= ~(1<<strobe3); //Strobe linija je ugasnjena da se izhod ne updejta
	PORTC |= (1<<output_en3);
	
	uint8_t temp;		
	int delay = 1;
	
	for(int i = 0; i < 16; i++)
	{
		if(i % 2 == 0)
		{
			temp = (bit & 1);
			
			if(temp)
			PORTC |= (1<<data3);
			else
			PORTC &= ~(1<<data3);
			
			bit = bit>>1;
		}

		if(i != 0)
		{
			PORTC ^= (1<<clock3);
			_delay_ms(delay);
		}
	}
	
	//PORTC |= (1<<strobe3);	//Vrednosti se updejtajo
	

	PORTC ^= (1<<clock3);		//konèni vrednosti za clock in data linijo
	PORTC &= ~(1<<data3);
	
	PORTC |= (1<<output_en3);
}

void izberiUre(uint8_t ure)
{
	switch (ure % 12)
	{
		case 0 :
		bit1 &= ~(1<<ena1) & ~(1<<dva1) & ~(1<<tri1) & ~(1<<stiri1) & ~(1<<pet1) & ~(1<<sest1) & ~(1<<sedem1);
		bit2 &= ~(1<<osem2) & ~(1<<devet2) & ~(1<<deset2) & ~(1<<enajst2);
		bit2 |= (1<<dvanajst2);
		break;
		
		case 1 :
		bit1 &= ~(1<<dva1) & ~(1<<tri1) & ~(1<<stiri1) & ~(1<<pet1) & ~(1<<sest1) & ~(1<<sedem1);
		bit2 &= ~(1<<osem2) & ~(1<<devet2) & ~(1<<deset2) & ~(1<<enajst2) & ~(1<<dvanajst2);
		bit1 |= (1<<ena1);
		break;
		
		case 2 :
		bit1 &= ~(1<<tri1) & ~(1<<ena1) & ~(1<<stiri1) & ~(1<<pet1) & ~(1<<sest1) & ~(1<<sedem1);
		bit2 &= ~(1<<osem2) & ~(1<<devet2) & ~(1<<deset2) & ~(1<<enajst2) & ~(1<<dvanajst2);
		bit1 |= (1<<dva1);
		break;
		
		case 3 :
		bit1 &= ~(1<<dva1) & ~(1<<ena1) & ~(1<<stiri1) & ~(1<<pet1) & ~(1<<sest1) & ~(1<<sedem1);
		bit2 &= ~(1<<osem2) & ~(1<<devet2) & ~(1<<deset2) & ~(1<<enajst2) & ~(1<<dvanajst2);
		bit1 |= (1<<tri1);
		break;
		
		case 4 :
		bit1 &= ~(1<<dva1) & ~(1<<ena1) & ~(1<<tri1) & ~(1<<pet1) & ~(1<<sest1) & ~(1<<sedem1);
		bit2 &= ~(1<<osem2) & ~(1<<devet2) & ~(1<<deset2) & ~(1<<enajst2) & ~(1<<dvanajst2);
		bit1 |= (1<<stiri1);
		break;
		
		case 5 :
		bit1 &= ~(1<<dva1) & ~(1<<ena1) & ~(1<<tri1) & ~(1<<stiri1) & ~(1<<sest1) & ~(1<<sedem1);
		bit2 &= ~(1<<osem2) & ~(1<<devet2) & ~(1<<deset2) & ~(1<<enajst2) & ~(1<<dvanajst2);
		bit1 |= (1<<pet1);
		break;
		
		case 6 :
		bit1 &= ~(1<<dva1) & ~(1<<ena1) & ~(1<<tri1) & ~(1<<stiri1) & ~(1<<pet1) & ~(1<<sedem1);
		bit2 &= ~(1<<osem2) & ~(1<<devet2) & ~(1<<deset2) & ~(1<<enajst2) & ~(1<<dvanajst2);
		bit1 |= (1<<sest1);
		break;
		
		case 7 :
		bit1 &= ~(1<<dva1) & ~(1<<ena1) & ~(1<<tri1) & ~(1<<stiri1) & ~(1<<pet1) & ~(1<<sest1);
		bit2 &= ~(1<<osem2) & ~(1<<devet2) & ~(1<<deset2) & ~(1<<enajst2) & ~(1<<dvanajst2);
		bit1 |= (1<<sedem1);
		break;
		
		case 8 :
		bit1 &= ~(1<<ena1) & ~(1<<dva1) & ~(1<<tri1) & ~(1<<stiri1) & ~(1<<pet1) & ~(1<<sest1) & ~(1<<sedem1);
		bit2 &= ~(1<<dvanajst2) & ~(1<<devet2) & ~(1<<deset2) & ~(1<<enajst2);
		bit2 |= (1<<osem2);
		break;
		
		case 9 :
		bit1 &= ~(1<<ena1) & ~(1<<dva1) & ~(1<<tri1) & ~(1<<stiri1) & ~(1<<pet1) & ~(1<<sest1) & ~(1<<sedem1);
		bit2 &= ~(1<<dvanajst2) & ~(1<<osem2) & ~(1<<deset2) & ~(1<<enajst2);
		bit2 |= (1<<devet2);
		break;
		
		case 10 :
		bit1 &= ~(1<<ena1) & ~(1<<dva1) & ~(1<<tri1) & ~(1<<stiri1) & ~(1<<pet1) & ~(1<<sest1) & ~(1<<sedem1);
		bit2 &= ~(1<<dvanajst2) & ~(1<<osem2) & ~(1<<devet2) & ~(1<<enajst2);
		bit2 |= (1<<deset2);
		break;
		
		case 11 :
		bit1 &= ~(1<<ena1) & ~(1<<dva1) & ~(1<<tri1) & ~(1<<stiri1) & ~(1<<pet1) & ~(1<<sest1) & ~(1<<sedem1);
		bit2 &= ~(1<<dvanajst2) & ~(1<<osem2) & ~(1<<devet2) & ~(1<<deset2);
		bit2 |= (1<<enajst2);
		break;
	}
}
void izberiMinuteinUre(uint8_t cas_ure, uint8_t cas_minute)
{
	if(cas_minute >= 0 && cas_minute < 5)
	{
		bit3 &= ~(1<<cez3) & ~(1<<do3) & ~(1<<pol3) & ~(1<<minut3) & ~(1<<petm3) & ~(1<<desetm3) & ~(1<<petanjstm3);
		izberiUre(cas_ure);
	}
	if(cas_minute >= 5 && cas_minute < 10)
	{
		bit3 &= ~(1<<do3) & ~(1<<pol3) & ~(1<<desetm3) & ~(1<<petanjstm3);
		bit3 |= (1<<petm3) | (1<<minut3) | (1<<cez3);
		izberiUre(cas_ure);
	}
	if(cas_minute >= 10 && cas_minute < 15)
	{
		bit3 &= ~(1<<do3) & ~(1<<pol3) & ~(1<<petm3) & ~(1<<petanjstm3);
		bit3 |= (1<<desetm3) | (1<<minut3) | (1<<cez3);
		izberiUre(cas_ure);
	}
	if(cas_minute >= 15 && cas_minute < 20)
	{
		bit3 &= ~(1<<do3) & ~(1<<pol3) & ~(1<<petm3) & ~(1<<desetm3);
		bit3 |= (1<<petanjstm3) | (1<<minut3) | (1<<cez3);
		izberiUre(cas_ure);
	}
	if(cas_minute >= 20 && cas_minute < 25)
	{
		bit3 &= ~(1<<cez3) & ~(1<<petm3) & ~(1<<petanjstm3);
		bit3 |= (1<<desetm3) | (1<<minut3) | (1<<do3) | (1<<pol3);
		izberiUre(cas_ure+1);
	}
	if(cas_minute >= 25 && cas_minute < 30)
	{
		bit3 &= ~(1<<cez3) & ~(1<<desetm3) & ~(1<<petanjstm3);
		bit3 |= (1<<petm3) | (1<<minut3) | (1<<do3) | (1<<pol3);
		izberiUre(cas_ure+1);
	}
	if(cas_minute >= 30 && cas_minute < 35)
	{
		bit3 &=  ~(1<<cez3) & ~(1<<do3) & ~(1<<minut3) & ~(1<<petm3) & ~(1<<desetm3) & ~(1<<petanjstm3);
		bit3 |= (1<<pol3);
		izberiUre(cas_ure+1);
	}
	if(cas_minute >= 35 && cas_minute < 40)
	{
		bit3 &= ~(1<<do3) & ~(1<<desetm3) & ~(1<<petanjstm3);
		bit3 |= (1<<petm3) | (1<<minut3) | (1<<cez3) | (1<<pol3);
		izberiUre(cas_ure+1);
	}
	if(cas_minute >= 40 && cas_minute < 45)
	{
		bit3 &= ~(1<<do3) & ~(1<<petm3) & ~(1<<petanjstm3);
		bit3 |= (1<<desetm3) | (1<<minut3) | (1<<cez3) | (1<<pol3);
		izberiUre(cas_ure+1);
	}
	if(cas_minute >= 45 && cas_minute < 50)
	{
		bit3 &= ~(1<<cez3) & ~(1<<petm3) & ~(1<<desetm3) & ~(1<<pol3);
		bit3 |= (1<<petanjstm3) | (1<<minut3) | (1<<do3);
		izberiUre(cas_ure+1);
	}
	if(cas_minute >= 50 && cas_minute < 55)
	{
		bit3 &= ~(1<<cez3) & ~(1<<petm3) & ~(1<<petanjstm3) & ~(1<<pol3);
		bit3 |= (1<<desetm3) | (1<<minut3) | (1<<do3);
		izberiUre(cas_ure+1);
	}
	if(cas_minute >= 55 && cas_minute < 60)
	{
		bit3 &= ~(1<<cez3) & ~(1<<desetm3) & ~(1<<petanjstm3) & ~(1<<pol3);
		bit3 |= (1<<petm3) | (1<<minut3) | (1<<do3);
		izberiUre(cas_ure+1);
	}
}