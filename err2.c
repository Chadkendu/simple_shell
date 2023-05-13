#include "p_shell.h"

char *err_pa(char **args);
char *err_rv(char **args);

/**
 * err_rv - function for commnad invalid
 *
 * Description:
 * @args: array arguments passed to command
 *
 * Return: string error
 */

char *err_rv(char **args)
{
	char *error, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hiStr);
		return (NULL);
	}

	p_strcpy(error, name);
	p_strcat(error, ": ");
	p_strcat(error, hiStr);
	p_strcat(error, ": ");
	p_strcat(error, args[0]);
	p_strcat(error, ": not found\n");

	free(hiStr);
	return (error);
}

/**
 * err_pa - function for permission denied errors
 *
 * Description:
 * @args: array of arguments passed to command.
 *
 * Return: string error
 */

char *err_pa(char **args)
{
	char *error, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hiStr);
		return (NULL);
	}

	p_strcpy(error, name);
	p_strcat(error, ": ");
	p_strcat(error, hist_str);
	p_strcat(error, ": ");
	p_strcat(error, args[0]);
	p_strcat(error, ": Permission denied\n");

	free(hiStr);
	return (error);
}
