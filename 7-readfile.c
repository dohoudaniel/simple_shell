#include "header.h"

/**
 * readfile - reads a file line by line and executes it as a command
 * @file: name of file to be used
 * @ess: should be null
 * @env: environment variables
 * @h: pointer to first element of a list
 * @num: number that controls freeing of environment variables
 * @av: name of the shell executable
 *
 * Return: 0 or -1
 */
int readfile(char *file, char *ess, char **env, list_t *h, int num, char *av)
{
	FILE *fpointer;
	struct stat statbuf;
	int error, len;
	size_t n;
	char *buffer = NULL;

	if (!file)
		return (-1);
	if (ess)
	{
		fprintf(stderr, "Usage: simple_shell filename\n");
		return (-1);
	}
	if (stat(file, &statbuf) != 0)
	{
		perror(file);
		return (-1);
	}
	if (!S_ISREG(statbuf.st_mode))
	{
		fprintf(stderr, "%s is not a regular file", file);
		return (-1);
	}
	fpointer = fopen(file, "r");

	while (!feof(fpointer))
	{
		getdelim(&buffer, &n, 10, fpointer);
		len = strlen(buffer);
		if (buffer[len - 1] == '\n')
			error = execute(buffer, env, num, h, av);
		else
			free(buffer);
	}
	fclose(fpointer);
	return (error);
}
