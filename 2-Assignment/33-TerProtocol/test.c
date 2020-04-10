#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int var1, var2, plus = 0, mul = 0, divide = 0;
	char ch1[4], ch2[4], *ptr, ch, optr[4];

	 printf("Enter 1st number: ");
	 scanf("%d", &var1);
	 printf("Enter 2st number: ");
	 scanf("%d", &var2);
	  
	 sprintf(ch1,"%d", var1);
	 sprintf(ch2,"%d", var2);
	 strcat(ch1,"+");
	 strcat(ch1,ch2);
	
	ptr = ch1;
	 while(*ptr != '\0')
	 {
	 	 ch = *ptr;
	 	 if(ch == '+')
	 	 	 plus = 1;
	 	else if(ch == '*')
	 		mul = 1;
	 	else if (ch == '/')
	 		divide = 1;
	 	else if( mul == 1 || plus == 1 || divide == 1)
	 		break;

	 	ptr++;

	 }
	 
	 printf("%d\n", plus);
	 printf("%d\n", mul);
	 printf("%d\n", divide);
}
