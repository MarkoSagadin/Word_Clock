/*
 * rtc.h
 *
 * Created: 16. 04. 2018 17:38:57
 *  Author: Marko
 */ 


#ifndef RTC_H_
#define RTC_H_

#include "i2c.h"

#define RTCwrite 0xD0		//Address for writing to RTC
#define RTCread  0xD1	//Address for reading from RTC
//Addresses for setting and reading different values
#define SECONDS  0x00
#define	MINUTES	 0x01u
#define HOURS	 0x02u
#define DAY		 0x03u
#define DATE	 0x04u
#define MONTH	 0x05u
#define YEAR     0x06u
#define CONTROL  0x0Eu
#define STATUS   0x0Fu

void rtcInit();
void sendTime();
void readTime();
void setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t weekDay, uint8_t date, uint8_t month, uint8_t year);
uint8_t getSec();
uint8_t decToBcd(uint8_t val);
uint8_t bcdToDec(uint8_t val);
	
extern uint8_t sec;
extern uint8_t min;
extern uint8_t hour;
extern uint8_t weekDay;
extern uint8_t date;
extern uint8_t month;
extern uint8_t year;	
	




#endif /* RTC_H_ */