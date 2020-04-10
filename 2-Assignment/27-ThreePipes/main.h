
#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 100

void one_command(char *buff[MAX]);
void two_command(char *buff_1[MAX], char *buff_2[MAX]);
void three_command(char *buff_1[MAX], char *buff_2[MAX], char *buff_3[MAX]);

#endif
