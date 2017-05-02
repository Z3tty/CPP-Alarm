#if defined(_WIN32)
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdarg.h>
	#include <time.h>
	#include <ctime>
	#include <windows.h>
	#include <mmsystem.h>

	int main(int argv, char **argc)
	{
		if(!argc[1] || !argc[2] || !argc[3]) throw "CLI Argument error: invoke with 'alarm h m s' ";
		int hour 	= 	atoi(argc[1]);
		int min 	= 	atoi(argc[2]);
		int sec 	= 	atoi(argc[3]);
		struct {int h; int m; int s;} tm_alarm;
		tm_alarm.h = hour; tm_alarm.m = min; tm_alarm.s = sec;

		int sleepTime = 5;
		bool alarm = false;
		do {
			::Sleep(sleepTime*1000);
			time_t time = std::time(0);
			struct tm *tm_now = localtime(&time);
			if((tm_alarm.h)		<=		(tm_now->tm_hour)			&&
			   (tm_alarm.m)		<=		(tm_now->tm_min)			&&
			   (tm_alarm.s)		<=		(tm_now->tm_sec)) {
				::PlaySound("Invalid link for BOING sound, replace with a link for custom music", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				alarm = true;
				for(int i = 0; i < 100000; i++) printf("ALARM\t ALARM\t ALARM\t ALARM\t ALARM");
			}
		}while(!alarm);
	}
#else
	throw "Unsupported operating system";
#endif
