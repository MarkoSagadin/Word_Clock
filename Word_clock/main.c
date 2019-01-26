#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdint.h>
#include "display.h"
#include "rtc.h"


//////////////////////////////
////  Makro definicije  //////
//////////////////////////////
#define gumbUre PORTB6			//INT0
#define gumbMinute PORTB7		//INT1
#define gumbPool 256-8			//Vsako 1ms preverim stanje gumbov
#define timeUpdate 65536-62500	//Prekinitev na 8 sekund


ISR (TIMER0_OVF_vect)          //Timer interupt za gumbe
{
	static uint8_t pushDownTimeUre =  0;
	static uint8_t pushDownTimeMinute =  0;
	if(PINB & 1<<gumbUre)
	{
		pushDownTimeUre++;
		if(pushDownTimeUre == 25)
		{
			pushDownTimeUre = 0;
			
			///////////////////
			hour++;
			if(hour == 24)
				hour = 0;
				
			izberiMinuteinUre(hour, min);
			bitshift1(bit1);
			bitshift2(bit2);
			bitshift3(bit3);
			PORTD |= 1<<strobe1;
			PORTD |= 1<<strobe2;
			PORTC |= (1<<strobe3);
			sendTime();
			///////////////////
			
			while(PINB & 1<<gumbUre);
		
		}
	}
	
	if(PINB & 1<<gumbMinute)
	{
		pushDownTimeMinute++;
		if(pushDownTimeMinute == 25)
		{
			pushDownTimeMinute = 0;
			
			///////////////////		
			min = min+5;
			
			if(min >= 60)
			{	
				
				hour++;
				min = min % 60;
				if(hour == 24)
					hour = 0;
			}
			izberiMinuteinUre(hour, min);
			bitshift1(bit1);
			bitshift2(bit2);
			bitshift3(bit3);
			PORTD |= 1<<strobe1;
			PORTD |= 1<<strobe2;
			PORTC |= (1<<strobe3);
			sendTime();
			///////////////////
			
			while(PINB & 1<<gumbMinute);
			
		}
	}

	TCNT0 = gumbPool;
}


ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	readTime();
	izberiMinuteinUre(hour, min);
	bitshift1(bit1);
	bitshift2(bit2);
	bitshift3(bit3);
	PORTD |= 1<<strobe1;
	PORTD |= 1<<strobe2;
	PORTC |= (1<<strobe3);
	
	TCNT1 = timeUpdate;
}



int main(void)
{
	DDRB &= ~(1<<gumbMinute) & ~(1<<gumbUre);		//Nastavljanje vhodov za proženje prekinitev
	
	DDRD |= (1<<strobe1) | (1<<data1) | (1<<clock1);
	PORTD &= ~(1<<strobe1) & ~(1<<clock1) & ~(1<<data1);
	DDRB |= (1<<output_en1);
	PORTB &= ~(1<<output_en1);
	
	DDRD |= (1<<strobe2) | (1<<clock2) | (1<<data2) | (1<<output_en2);
	PORTD &= ~(1<<strobe2) & ~(1<<clock2) & ~(1<<data2) & ~(1<<output_en2);

	
	DDRC |= (1<<strobe3) | (1<<clock3) | (1<<data3) | (1<<output_en3);
	PORTC &= ~(1<<strobe3) & ~(1<<clock3) & ~(1<<data3) & ~(1<<output_en3);

	DDRB |= (1<<PORTB1);
	PORTB |= (1<<PORTB1);	
	
	
	
	rtcInit();
	//sendTime();  //Samo ko nastavljaš na novo èas
	readTime();
	izberiMinuteinUre(hour, min);
	bitshift1(bit1);
	bitshift2(bit2);
	bitshift3(bit3);
	PORTD |= 1<<strobe1;
	PORTD |= 1<<strobe2;
	PORTC |= (1<<strobe3);
	
	///////////////////////////////////////
	//Nastavitev števca za updejtanje ure//
	///////////////////////////////////////
	TCNT1 = timeUpdate;   // for 1 sec at 16 MHz
	TCCR1A = 0x00;
	TCCR1B |= (1<<CS10) | (1<<CS12);  // Timer mode with 1024 prescler
	TIMSK1 = (1 << TOIE1) ; // Enable timer1 overflow interrupt(TOIE1)
	sei();
	
	///////////////////////////////////////
	//Nastavitev števca za preverjanje gumbov//
	///////////////////////////////////////
	TCNT0 = gumbPool;   // for 1 sec at 16 MHz
	TCCR0A = 0x00;
	TCCR0B |= (1<<CS10) | (1<<CS12);  // Timer mode with 1024 prescler
	TIMSK0 = (1 << TOIE1) ; // Enable timer0 overflow interrupt(TOIE0)
	sei();
	

    while (1) 
	{
	}
}
