#include "main.h"

/**
 * main - requests commands from the user and execute them
 * @argc: number of arguments
 * @argv: list of arguments
 * @env: environment variables
 *
 * Return: 1 on success and -1 on failure
 */
int main(int argc, char *argv[], char *env[])
{
	char *lineptr = NULL;
	int str_count;
	size_t len = 0;
	ssize_t nread;
	pid_t child;
	int status;
	struct stat st;

	printf("$ ");
	while ((nread = getline(&lineptr, &len, stdin) != EOF))
	{
		str_count = strlen(lineptr);
		lineptr[str_count - 1] = '\0';

		if (stat(lineptr, &st) == 0)
		{
			child = fork();
			if (child == -1)
				return (-1);
			if (child == 0)
			{
				char *_argv[] = {lineptr, NULL};

				execve(_argv[0], _argv, env);
			}
			else
			{
				wait(&status);
			}
		}
		else
		{
			printf("%s: No such file or directory.\n", argv[0]);
		}
		printf("$ ");
	}
	free(lineptr);
	return (1);
}
