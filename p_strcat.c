#include "p_shell.h"

/**
 * p_strcat - function to concatenates two strings
 *
 * Description:
 * @dest: pointer to first string
 * @src: pointer to second string
 *
 * Return: pointer to the concatenated string
 * or NULL if allocation fails
 *
 */

char *p_strcat(char *dest, char *src)
{
	char *concat_str, *result;/** declare pointer to char **/
	int len_dest, len_src, len_concat, b = 0, d = 0;

	len_dest = strlen(dest);/** get dest string length **/
	len_src = strlen(src);/** get length of src string **/
	len_concat = len_dest + len_src + 1;/** calc concatenated string length **/
	concat_str = malloc(sizeof(char) * len_concat);/** allocate memory for
							* concat string **/
	if (concat_str == NULL)
		return (NULL);
	for (b = 0; b < len_dest; b++)/** cpoy chars fro dest to concat_string **/
	{
		concat_str[b] = dest[b];
	}
	while (*(src + d))/** append chars from src to concat_string **/
	{
		*(concat_str + 1) = *(src + d);
		b++;
		d++;
	}
	concat_str[b] = '\0';
	result = concat_str;
	return (result);
}
