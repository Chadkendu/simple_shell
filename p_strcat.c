#include "p_shell.h"

char *p_strncat(char *dest, const char *src, size_t w);
char *p_strcat(char *dest, const char *src);
int p_strlent(const char *sr);
char *p_strcpy(char *dest, const char *src);

/**
 * p_strcpy - Copies the string to buffer
 *
 * Description:
 * @dest: Pointer to string destination
 * @src: Pointer to source string
 *
 * Return: dest pointer
 */

char *p_strcpy(char *dest, const char *src)
{
	size_t b;

	for (b = 0; src[b] != '\0'; b++)
	{
		dest[b] = src[b];
	}
	dest[b] = '\0';
	return (dest);
}

/**
 * p_strlent - returns string length
 *
 * Description:
 * @sr: string character pointer
 *
 * Return: character string length
 */

int p_strlent(const char *sr)
{
	int length = 0;

	if (!sr)
	{
		return (length);
	}
	for (length = 0; sr[length]; length++)
		;
	return (length);
}

/**
 * p_strncat - string concatenation
 *
 * Description:
 * @dest: string destination pointer
 * @src: string source pointer
 * @w: bytes to copy from src.
 *
 * Return: string destination pointer
 */

char *p_strncat(char *dest, const char *src, size_t w)
{
	size_t destLength = p_strlent(dest);
	size_t b;

	for (b = 0; b < w && src[b] != '\0'; b++)
	{
		dest[destLength + b] = src[b];
	}
	dest[destLength + b] = '\0';

	return (dest);
}

/**
 * p_strcat - string concatenation
 *
 * Description:
 * @dest: string destination pointer
 * @src: string source pointer
 *
 * Return: string destination pointer
 */

char *p_strcat(char *dest, const char *src)
{
	char *destemp;
	const char *srcemp;

	destemp = dest;
	srcemp =  src;

	while (*destemp != '\0')
	{
		destemp++;
	}

	while (*srcemp != '\0')
	{
		*destemp++ = *srcemp++;
	}
	*destemp = '\0';
	return (dest);
}
