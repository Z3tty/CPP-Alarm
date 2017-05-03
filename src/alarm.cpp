#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>

int main(int argc, char **argv) // Command line arguments
{
	if (argc < 4 || argc > 4){ printf("USAGE: %s HOUR MIN SEC", argv[0]); return 1; } // Enforce input
	int hour 	= 	atoi(argv[1]); // Get ints
	int min 	= 	atoi(argv[2]);
	int sec 	= 	atoi(argv[3]);

	while((hour >24 || min >=60 || sec >=60)) { // Enforce adherence to the format (0-24)/(0-60)/(0-60)
		if(hour>  25) 	{ hour -= 24; 			}
		if(min >= 60)  	{ min -= 60; hour++; 	}
		if(sec >= 60)	{ sec -= 60; min++;	 	}
	}

	printf("Alarm set for: %d:%d:%d\n", hour, min, sec); // Tell the user the alarm time
	struct { int h; int m; int s; } tm_alarm; // Alarm time object
	tm_alarm.h = hour; tm_alarm.m = min; tm_alarm.s = sec; // Init the struct member values
	int sleepTime = 5; // Sleep time inbetween time-checks, in seconds
	bool alarm = false, closed = false; // Loopvariables

	do {
		closed = false; // For the extension ability
		time_t time = std::time(0); // the time now
		struct tm *tm_now = localtime(&time); // Struct it

		if ((tm_alarm.h < tm_now->tm_hour) 									|| // Checks
		   (tm_alarm.h == tm_now->tm_hour && tm_alarm.m <= tm_now->tm_min) 	||
		   (tm_alarm.h == tm_now->tm_hour && tm_alarm.m == tm_now->tm_min && tm_alarm.s <= tm_now->tm_sec))
		    {
			while(!closed) { // Play the alarm sounds
				::PlaySound("Invalid link for BOING sound, replace with a link for custom music", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				alarm = true;
				char c;
				std::cin >> c; // Get input
				if(c == 'c') { closed = true; return 0; }
				else if(c == 'e') {
					// Ensure that extensions dont loop wrongfully
					if(tm_alarm.m+10 >= 60) { tm_alarm.h += 1; tm_alarm.m =abs((tm_alarm.m+10)-60); }
					else tm_alarm.m += 10; 
					alarm = false;
					closed = true;
					::PlaySound(NULL, NULL, 0);
					printf("Alarm extended by 10min to: %d:%d:%d\n", tm_alarm.h, tm_alarm.m, tm_alarm.s);
				} else { printf("Invalid input: %c", c); }
				::Sleep(1250); // Time inbetween sounds
			}
		::Sleep(sleepTime * 1000); // Wait between checks
		}
	} while (!alarm);
	return 0;
}
