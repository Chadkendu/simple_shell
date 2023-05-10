#include "p_shell.h"

/** function declaration p_strcspn **/
size_t p_strcspn(const char *strg, char k);


/**
 * parv - function that executes a command
 *
 * Description:
 * @arv: argument vector
 * @envr: environment vector
 *
 * Return: Always 0(success)
 *
 */

void parv(char **arv, char **envr)
{
	pid_t child_pid;
	int stats;
	char *strng = NULL;
	char *argv[] = {NULL, NULL};
	size_t w = 0;
	ssize_t numb_char;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("cimba$ ");

		numb_char = getline(&strng, &w, stdin);
		if (numb_char == -1)
		{
			free(strng);
			exit(EXIT_FAILURE);
		}

		strng[p_strcspn(strng, '\n')] = 0;

		argv[0] = strng;

		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, envr) == -1)
				printf("%s file or directory not found\n", arv[0]);
		}
		else
			wait(&stats);
	}
	exit(EXIT_SUCCESS);
}

/**
 * p_strcspn - function to calc length of char number
 *
 * Description:
 * @strg: string
 * @k: character
 *
 * Return: index of @k ot the total num of chars
 *
 */

size_t p_strcspn(const char *strg, char k)
{
	size_t b = 0;

	do {
		if (strg[b] == k)
		{
			return (b);
		}
		++b;
	} while (strg[b - 1] != '\0');
	return (b);
}
