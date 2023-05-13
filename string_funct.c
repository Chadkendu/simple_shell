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

/**
 * p_strcmp - compares two string
 *
 * Description:
 * @str1: first string
 * @str2: second string
 *
 * Return: if both are same (0), otherwise (1)
 *
 */

int p_strcmp(char *str1, char *str2)
{
	int index = 0, str_length;

	str_length = p_strlent(str1);
	while (str2[index] != '\0')
	{
		if (str2[index] != str1[index])
			return (1);
		index++;
	}
	if (str_length != index)
	{
		return (1);
	}
	return (0);
}

/**
 * p_strcat - concatenate two string
 *
 * Description:
 * @destination: String destination
 * @source: string source
 *
 * Return: concatenated string
 *
 */

char *p_strcat(char *destination, char *source)
{
	int index_dest, index_src, dest_length, src_length, new_length;
	char *new;

	dest_length = p_strlent(destination);
	src_length = p_strlent(source);
	new_length = dest_length + src_length + 1;
	new = malloc(sizeof(char) * new_length);
	if (new == NULL)
		return (NULL);

	/** copies new to destination **/
	for (index_dest = 0; index_dest < dest_length; index_dest++)
		new[index_dest] = destination[index_dest];

	index_src = 0;
	while (index_src < src_length)
		new[index_dest] = source[index_src], index_dest++, index_src++;

	new[index_dest] = '\0';
	return (new);
}
