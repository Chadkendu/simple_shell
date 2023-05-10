#include "p_shell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * prstrtok - function that print a string
 *
 * Description:
 * @strg: string to print
 *
 * Return: string arrays
 *
 */

char **prstrtok(char *strg)
{
	char **arstr;
	int b = 0;

	/** allocate memory for token array **/
	arstr = malloc(8 * sizeof(char *));
	if (arstr == NULL)
	{
		perror("Can't allocate memory");
		exit(1);
	}

	/** tokenize the string input usind a delimeter(space) **/
	arstr[b] = strtok(strg, " ");
	while (arstr[b] != NULL)
	{
		b++;
		arstr[b] = strtok(NULL, " ");
	}

	/** return token array **/
	return (arstr);
}
