#include "p_shell.h"

char *err_env(char **args);
char *err_uno(char **args);
char *err_exit(char **args);
char *err_cd(char **args);
char *err_syntax(char **args);

/**
 * err_syntax - function for syntax message errors
 *
 * Description:
 * @args: array arguments passed to command
 *
 * Return: string error
 */

char *err_syntax(char **args)
{
	char *erro, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 33;
	erro = malloc(sizeof(char) * (length + 1));
	if (!erro)
	{
		free(hiStr);
		return (NULL);
	}

	p_strcpy(erro, name);
	p_strcat(erro, ": ");
	p_strcat(erro, hiStr);
	p_strcat(erro, ": Syntax Invalid \"");
	p_strcat(erro, args[0]);
	p_strcat(erro, "\" not expected\n");

	free(hiStr);
	return (erro);
}

/**
 * err_exit - function for the parv_exit error messsage
 *
 * Description:
 * @args: array of arguments passed to command.
 *
 * Return: string error
 */

char *err_exit(char **args)
{
	char *erro, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 27;
	erro = malloc(sizeof(char) * (length + 1));
	if (!erro)
	{
		free(hiStr);
		return (NULL);
	}

	p_strcpy(erro, name);
	p_strcat(erro, ": ");
	p_strcat(erro, hiStr);
	p_strcat(erro, ": Number invalid ");
	p_strcat(erro, args[0]);
	p_strcat(erro, "\n");

	free(hiStr);
	return (erro);
}

/**
 * err_cd - function for the parv_cd error message
 *
 * Description:
 * @args: array of arguments passed to command
 *
 * Return: string error
 */

char *err_cd(char **args)
{
	char *erro, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		p_strcat(erro, ": cd$ Invalid option ");
	else
		p_strcat(erro, ": cd$ can't cd ");
	p_strcat(erro, args[0]);
	p_strcat(erro, "\n");

	free(hiStr);
	return (erro);
}

/**
 * err_uno - function for the parv_alias error message
 *
 * Description:
 * @args: array arguments passed to command
 *
 * Return: string error
 */

char *err_uno(char **args)
{
	char *erro;
	int length;

	length = p_strlent(name) + p_strlent(args[0]) + 13;
	erro = malloc(sizeof(char) * (length + 1));
	if (!erro)
		return (NULL);

	p_strcpy(erro, "alias$ ");
	p_strcat(erro, args[0]);
	p_strcat(erro, " not found\n");

	return (erro);
}

/**
 * err_env - function for the parv_env exit process
 *
 * Description:
 * @args: array arguments passed to command
 *
 * Return: string error
 */

char *err_env(char **args)
{
	char *erro, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	args--;
	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 45;
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
	p_strcat(erro, ": Can't add or remove from environment\n");

	free(hiStr);
	return (erro);
}
