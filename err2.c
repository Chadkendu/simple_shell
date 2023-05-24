#include "p_shell.h"

char *err_pa(char **args);
char *err_rv(char **args);

char *name;
int hist_count;

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
	char *erro, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 16;
	erro = malloc(sizeof(char) * (length + 1));
	if (!erro)
	{
		free(hiStr);
		return (NULL);
	}

	p_strcpy(erro, name);
	p_strcat(erro, ": ");
	p_strcat(erro, hiStr);
	p_strcat(erro, ": ");
	p_strcat(erro, args[0]);
	p_strcat(erro, ": not found\n");

	free(hiStr);
	return (erro);
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
	char *erro, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 24;
	erro = malloc(sizeof(char) * (length + 1));
	if (!erro)
	{
		free(hiStr);
		return (NULL);
	}

	p_strcpy(erro, name);
	p_strcat(erro, ": ");
	p_strcat(erro, hiStr);
	p_strcat(erro, ": ");
	p_strcat(erro, args[0]);
	p_strcat(erro, ": Permission denied\n");

	free(hiStr);
	return (erro);
}
