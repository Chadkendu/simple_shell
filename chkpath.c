#include "p_shell.h"

/**
 * chkpath - checks if given string begins with /bin/
 *
 * Description:
 * @input: Checked string
 *
 * Return: 1 (found), 0(not found)
 *
 */

int chkpath(char *input)
{
	/** allocate memory to suffix **/
	char *suffix = malloc(sizeof(char) * 50);
	char *prefix = "/bin/", *d;
	int b, q = 0;

	if (suffix == NULL)/** check if memory alloc is success **/
	{
		free(suffix);
		return (1);
	}

	/** loop through prefix to comapre input **/
	for (b = 0; prefix[b] != '\0'; b++)
	{
		if (prefix[b] != input[b])
		{
			free(suffix);
			return (0);
		}
	}

	/** loop through input prefix and stroe suffix in new array **/
	b = 0;
	while (input[b] != '\0')
	{
		suffix[q] = input[b];
		q++;
		b++;
	}
	suffix[q] = '\0';

	d = chkfile(suffix);
	if (d == NULL)
	{
		free(suffix);
		return (1);
	}
	free(suffix);
	return (0);
}
