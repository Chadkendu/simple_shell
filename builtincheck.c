#include "p_shell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * builtincheck - function to check if builtin command can be executed
 * without forking it
 *
 * Description:
 * @strg: string for builtin command
 *
 * Return: 1(false), 0(true)
 *
 */

int builtincheck(char *strg)
{
	char *arry[] = {"exit", "help", "cd"};
	int b = 0;
	char *usern;

	for (b = 0; b < 3; b++)
	{
		if (strcmp(arry[b], strg) == 0)
		{
			break;
		}
		b++;
	}
	b++;
	switch (b)
	{
		case 1:
			chdir(strg);
			return (1);
		case 2:
			write(STDOUT_FILENO, "welcome", 2);
			return (2);
		case 3:
			usern = getenv("HOSTNAME");
			printf("%s you are welcome\n", usern);
			return (1);
		default:
			return (0);
	}
	return (0);
}
