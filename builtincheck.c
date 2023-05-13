#include "p_shell.h"

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
	char **arry;
	int b = 0;
	char *usern;

	arry = malloc(sizeof(char *) * 3);
	if (arry == NULL)
		return (0);
	arry[0] = "help";
	arry[1] = "cd";
	arry[2] = "exit";

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
			free(arry);
			return (1);
		case 2:
			write(STDOUT_FILENO, "welcome", 2);
			free(arry);
			return (2);
		case 3:
			usern = getenv("HOSTNAME");
			printf("%s you are welcome\n", usern);
			free(arry);
			return (1);
		default:
			free(arry);
			return (0);
	}
	return (0);
}
