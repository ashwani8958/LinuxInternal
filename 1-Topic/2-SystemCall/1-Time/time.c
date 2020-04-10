#include <stdio.h>
#include <time.h>

int main()
{
	time_t mytime, mytime_in_year;

	//mytime = time(NULL);

	time(&mytime);

	mytime_in_year = mytime/(60*60*24*365);

	printf("Time in second since 1970:- %ld\nTime in year since 1970:- %ld\n", mytime, mytime_in_year);
	return 0;
}
