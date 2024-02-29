#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]);
int execute_command(char *lineptr, char *argv[], char *env[]);

#endif
