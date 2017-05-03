#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>

int main(int argc, char **argv)
{
	if (argc < 4 || argc > 4) printf("USAGE: %s HOUR MIN SEC", argv[0]);
	int hour 	= 	atoi(argv[1]);
	int min 	= 	atoi(argv[2]);
	int sec 	= 	atoi(argv[3]);
	while((hour >24 || min >=60 || sec >=60)) {
		if(hour>  25) 	{ hour -= 24; 			}
		if(min >= 60)  	{ min -= 60; hour++; 	}
		if(sec >= 60)	{ sec -= 60; min++;	 	}
	}
	printf("Alarm set for: %d:%d:%d\n", hour, min, sec);
	struct { int h; int m; int s; } tm_alarm;
	tm_alarm.h = hour; tm_alarm.m = min; tm_alarm.s = sec;
	int sleepTime = 5;
	bool alarm = false, closed = false;
	do {
		closed = false;
		::Sleep(sleepTime * 1000);
		time_t time = std::time(0);
		struct tm *tm_now = localtime(&time);
		if ((tm_alarm.h) <= (tm_now->tm_hour) &&
			(tm_alarm.m) <= (tm_now->tm_min) &&
			(tm_alarm.s) <= (tm_now->tm_sec)) {
			while(!closed) {
				::PlaySound("Invalid link for BOING sound, replace with a link for custom music", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				alarm = true;
				char c;
				std::cin >> c;
				if(c == 'c') { closed = true; return 0; }
				else if(c == 'e') {
					if(tm_alarm.m+10 >= 60) { tm_alarm.h += 1; tm_alarm.m +=(tm_alarm.m-60)+10; }
					else tm_alarm.m += 10; 
					alarm = false;
					closed = true;
					::PlaySound(NULL, NULL, 0);
					printf("Alarm extended by 10min to: %d:%d:%d\n", tm_alarm.h, tm_alarm.m, tm_alarm.s);
				}
				::Sleep(1250);
			}
		}
	} while (!alarm);
}
