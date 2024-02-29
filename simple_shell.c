#include "main.h"

/**
 * execute_command - executes command
 * @lineptr: command read from the user
 * @argv: command sent to the program
 * @env: enviroment variables
 *
 * Return: 0 on success or -1 on failure
 */
int execute_command(char *lineptr, char *argv[], char *env[])
{
	char *_argv[2];
	int str_count, status;
	pid_t child;
	struct stat st;

	str_count = strlen(lineptr);
	lineptr[str_count - 1] = '\0';
	if (stat(lineptr, &st) == 0)
	{
		child = fork();
		if (child == -1)
			return (-1);
		if (child == 0)
		{
			_argv[0] = lineptr;
			_argv[1] = NULL;
			execve(_argv[0], _argv, env);
		}
		else
		{
			wait(&status);
		}
	}
	else
		printf("%s: No such file or directory.\n", argv[0]);
	return (0);
}

/**
 * main - requests commands from the user and execute them
 * @argc: number of arguments
 * @argv: list of arguments
 * @env: environment variables
 *
 * Return: 0 on success and -1 on failure
 */
int main(int argc, char *argv[], char *env[])
{
	char *lineptr = NULL;
	size_t len = 0;
	ssize_t nread;

	if (argc == 0)
		return (-1);

	if (isatty(STDIN_FILENO))
	{
		printf("$ ");
		while ((nread = getline(&lineptr, &len, stdin) != EOF))
		{
			execute_command(lineptr, argv, env);
			printf("$ ");
		}
	}
	else
	{
		nread = getline(&lineptr, &len, stdin);
		execute_command(lineptr, argv, env);
	}
	free(lineptr);
	return (0);
}
