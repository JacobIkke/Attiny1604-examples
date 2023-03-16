/*
 * rtc_1604.h
 *
 * Created: 27-1-2023 19:23:41
 *  Author: PeetGaming
 */ 

#ifndef datetime1604_H_
#define datetime1604_H_

struct datetime {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint16_t year;
};

struct datetime datetimenow;

void RTC_init(void);
uint16_t timestamp(); 

#endif /* datetime1604_H_ */