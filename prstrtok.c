#include "p_shell.h"

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
	char **arstr, *pString;
	int b = 0, d = 0;

	/** allocate memory for token array **/
	arstr = malloc(8 * sizeof(char *));
	if (arstr == NULL)
	{
		perror("Can't allocate memory");
		exit(1);
	}

	/** tokenize the string input usind a delimeter(space) **/
	pString = strtok(strg, " ");
	while (pString != NULL)
	{
		while (pString[d])
		{
			if (pString[d] == '\n')
				pString[d] = '\0';
			d++;
		}
		arstr[b] = pString;
		b++;
		d = 0;
		pString = strtok(NULL, " ");
	}

	/** return token array **/
	arstr[b] = NULL;
	return (arstr);
}
