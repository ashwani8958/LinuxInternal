#include <stdio.h>
#include <sys/time.h>

int main()
{

	//struct timezone mytimezone;
	struct timeval mytime;
	//gettimeofday(&mytime, &mytimezone);
	gettimeofday(&mytime, NULL);


	printf("Time in second %ld\n", mytime.tv_sec);
	printf("Time in microsecond %d\n", mytime.tv_usec);
	//printf("Time in minutes west to greenwhich %d\n", mytime.tz_mintueswest);
	//printf("DST correction %d\n", mytime.tz_dsttime);
	return 0;
}
