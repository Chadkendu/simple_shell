#include "p_shell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * chkfile - function to check if given string is present
 *
 * Description:
 * @strg: the string to search files
 *
 * Return: if string is present(1), not present(0);
 *
 */

int chkfile(char *strg)
{
	int b = 0, w = 0; /** initialize int variable to 0 **/
	char *line, d; /** declare char pointer line and d **/
	FILE *file; /** declare file pointer **/

	line = malloc(sizeof(char) * 50); /** allocate memoey **/
	if (line == NULL)
		return (0);

	file = fopen("words.txt", "r");
	if (file == NULL)
	{
		perror("Can't open file");
		free(line);
		return (0);
	}

	while (!feof(file))
	{
		d = fgetc(file);
		line[w] = d;
		if (d == '\n')
		{
			line[w] = '\0';
			if (p_strcmp(line, strg) == 0)
			{
				free(line);
				fclose(file);
				return (1);
			}
			w = -1;
		}
		w = w + 1;
		b++;
	}

	line[w] = '\0';
	if (p_strcmp(line, strg) == 0)
	{
		free(line);
		fclose(file);
		return (1);
	}

	free(line);
	fclose(file);
	return (0);
}
