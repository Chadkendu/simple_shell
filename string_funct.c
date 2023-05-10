#include "p_shell.h"

/**
 * p_strlent - computes the lenght of a string
 * excluding the null byte
 *
 * Description:
 * @str: pointer to the string measured
 *
 * Return: string length
 *
 */

int p_strlent(char *str)
{
	int b = 0;

	while (str[b] != '\0')
	{
		b++;
	}
	return (b);
}

/**
 * p_strcspn - finds the index of characteer located in string
 *
 * Description:
 * @str: pointer to the searched string
 * @k: character target to search
 *
 * Return: index of @k if valid
 * or the total characteer number if invalid
 *
 */

size_t p_strcspn(const char *str, char k)
{
	size_t b = 0;

	for (; str[b]; b++)
	{
		if (str[b] == k)
			return (b);
	}
	return (b);
}
