#include <stdio.h>
#include "header.h"

/**
 * main - prints input from the user
 * @ac: argument count
 * @av: argument vector
 * @env: environment variables
 *
 * Return: 0
 */
int main(__attribute__((unused)) int ac, char **av, char **env)
{
	char *buffer;
	size_t n = 0;
	int i;
	char **arr;
	int err = 0;

	printf("#cisfun$ ");
	while ((i = getline(&buffer, &n, stdin)) != -1)
	{
		arr = split_string(buffer);
		if (strncmp(arr[0], "printenv", 8) == 0)
			_printenv(env);
		else if (strncmp(arr[0], "exit", 4) == 0)
			exit(err);
		else
			err = get_operator(arr, env, av[0]);
		if (i == -1)/* || i == EOF)*/
			return (-1);
		/*printf("%s", buffer);*/
		printf("#cisfun$ ");
	}
	return (0);
}
