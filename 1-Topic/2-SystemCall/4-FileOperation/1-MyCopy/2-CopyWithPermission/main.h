
#ifndef MAIN_H

#define MAIN_H

#include <sys/types.h>
#include <utime.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include <string.h>

#define MAX 100

int open_file_read(char argv[MAX]);
int open_file_write(char argv[MAX]);
int copy(int fd_r, int fd_w, char *argv[]);
int copy_content(int fd_r, int fd_w);
#endif


