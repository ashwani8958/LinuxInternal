#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

//Declare global variable, its value will be change upon calling 
//alarm function
int sig;

int set_alarm()
{
	unsigned int hrs, mins, secs, date, month, year;
	time_t alarm_time;
	struct tm *tm, tm_copy;
	time_t bak_time;

	while(1)
	{
		bak_time = time(NULL);
		tm = localtime(&bak_time);
		tm_copy = *tm;

		printf("Enter the alarm date DD/MM/YYYY ");
		scanf("%u/%u/%u", &date, &month, &year);
		printf("Enter the alarm time HH:MM:SS ");
		scanf("%u:%u:%u", &hrs, &mins, &secs);

		if(((hrs > 23) || (mins > 59) || (secs > 59)) || ((date < tm_copy.tm_mday) || ( month < tm_copy.tm_mon + 1) || (year < tm_copy.tm_year + 1900) ))
		{
			printf("Invalid time/date entered\n");
			continue;
		}

		bak_time = time(NULL);
		tm = localtime(&bak_time);
		tm_copy = *tm;


		tm_copy.tm_sec = secs;
		tm_copy.tm_min = mins;
		tm_copy.tm_hour = hrs;
		tm_copy.tm_mday = date;
		tm_copy.tm_mon = month - 1;
		tm_copy.tm_year = year - 1900;

		if(timelocal(&tm_copy) < bak_time)
		{
			printf("Invalid time entered here\n");
			continue;
		}

		else
		{
			break;
		}
	}

	alarm_time = timelocal(&tm_copy) - bak_time;
	printf("%ld\n", alarm_time);

	return alarm_time;
}

//Alarm Handler
void my_alarm(int signum)
{
	unsigned int alarm_time, choice;
	time_t time_var;

	time_var = time(NULL);

	printf("Alarm Expired %s\n", ctime(&time_var));

	printf("\n");
	printf("1. Set New Alarm\n2. Exit\nPlease enter your choice: ");
	scanf("%d", &choice);

	switch(choice)
	{
		case 1: 
		{
			alarm_time = set_alarm();
			alarm(alarm_time);
			break;
		}
		case 2:
		{
			exit(1);
		}
	}

	return;

}


int main(int argc , char *argv[])
{
	unsigned int alarm_time;
	int option;

	if (signal(SIGALRM, my_alarm) != NULL)
	{
		perror("signal");
		return 0;
	}

	alarm_time = set_alarm();
	alarm(alarm_time);
	
	while(1);

	return 0;
}
