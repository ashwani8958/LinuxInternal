#include <stdio.h>
#include <time.h>

int main()
{
	time_t mytime;
	struct tm *tm_var;
	char *sptr;
	//mytime = time(NULL);

	time(&mytime);

	tm_var = localtime(&mytime);

	sptr = ctime(&mytime);

	printf("\n%s\n", sptr);
	//printf("time is %ld\n", mytime);

	printf("Second : %d\n", tm_var->tm_sec);
	printf("minutes : %d\n", tm_var->tm_min);
	printf("hours : %d\n", tm_var->tm_hour);
	printf("day : %d\n", tm_var->tm_mday);
	printf("mon : %d\n", tm_var->tm_mon + 1); //month (0 - 11)
	printf("year : %d\n", tm_var->tm_year + 1900);
	printf("day of a weak : %d\n", tm_var->tm_wday);
	printf("day of year : %d\n", tm_var->tm_yday);
	printf("daylight saving time : %d\n", tm_var->tm_isdst);



	return 0;
}
