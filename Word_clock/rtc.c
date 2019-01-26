/*
 * rtc.c
 *
 * Created: 16. 04. 2018 17:38:46
 *  Author: Marko
 */ 

#include "i2c.h"
#include "rtc.h"



uint8_t sec;
uint8_t min;
uint8_t hour;
uint8_t weekDay;
uint8_t date;
uint8_t month;
uint8_t year;

void rtcInit()
{
	init();			
	startRtc();
	write(RTCwrite);
	write(0x0E); //address
	write(0x00);
	stop();
}
void sendTime()
{
	startRtc();
	write(0xD0);
	write(0x00);
	write(decToBcd(sec));
	write(decToBcd(min));
	write(decToBcd(hour));
	write(decToBcd(weekDay));
	write(decToBcd(date));
	write(decToBcd(month));
	write(decToBcd(year));
	stop();
}

void readTime()
{
	startRtc();
	write(RTCwrite);
	write(SECONDS);
	
	startRtc();
	write(RTCread);
	sec=bcdToDec(read(1) & 0x7f);
	min=bcdToDec(read(1));
	hour=bcdToDec(read(1) & 0x3f);
	weekDay=bcdToDec(read(1));
	date=bcdToDec(read(1));
	month=bcdToDec(read(1));
	year=bcdToDec(read(0));
	stop();
}
void setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t weekDay, uint8_t date, uint8_t month, uint8_t year)
{
	sec=decToBcd(sec);
	min=decToBcd(min);
	hour=decToBcd(hour);
	weekDay=decToBcd(weekDay);
	date=decToBcd(date);
	month=decToBcd(month);
	year=decToBcd(year);
}

// Convert decimal to binary numbers
uint8_t decToBcd(uint8_t val)
{
	return( (val/10*16) + (val%10) );
}
// Convert binary to decimal numbers
uint8_t bcdToDec(uint8_t val)
{
	return( (val/16*10) + (val%16) );
}
