#include "p_shell.h"

/**
 * chkfile - function to check if given string is present
 *
 * Description:
 * @strg: the string to search files
 *
 * Return: if string is present(1), not present(0);
 *
 */

char *chkfile(char *strg)
{
	int b = 0, w = 0; /** initialize int variable to 0 **/
	char *line, d, *cart; /** declare char pointer line and d **/
	FILE *file; /** declare file pointer **/

	line = malloc(sizeof(char) * 50); /** allocate memoey **/
	if (line == NULL)
		return (NULL);
	file = fopen("words.txt", "r");
	if (file == NULL)
		return (NULL);

	while (!feof(file))
	{
		d = fgetc(file);
		line[w] = d;
		if (d == '\n')
		{
			line[w] = '\0';
			if (p_strcmp(line, strg) == 0)
			{
				cart = p_strcat("/bin/", strg);
				free(line);
				fclose(file);
				return (cart);
			}
			w = -1;
		}
		w = w + 1;
		b++;
	}
	line[w] = '\0';
	if (p_strcmp(line, strg) == 0)
	{
		cart = p_strcat("/bin/", strg);
		free(line);
		fclose(file);
		return (cart);
	}
	free(line), fclose(file);
	return (NULL);
}
