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
	char *error, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 33;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hiStr);
		return (NULL);
	}

	p_strcpy(error, name);
	p_strcat(error, ": ");
	p_strcat(error, hiStr);
	p_strcat(error, ": Syntax Invalid \"");
	p_strcat(error, args[0]);
	p_strcat(error, "\" not expected\n");

	free(hiStr);
	return (error);
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
	char *error, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 27;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hiStr);
		return (NULL);
	}

	p_strcpy(error, name);
	p_strcat(error, ": ");
	p_strcat(error, hiStr);
	p_strcat(error, ": Number invalid ");
	p_strcat(error, args[0]);
	p_strcat(error, "\n");

	free(hiStr);
	return (error);
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
	char *error, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hiStr);
		return (NULL);
	}

	p_strcpy(error, name);
	p_strcat(error, ": ");
	p_strcat(error, hiStr);
	if (args[0][0] == '-')
		p_strcat(error, ": cd$ Invalid option ");
	else
		p_strcat(error, ": cd$ can't cd ");
	p_strcat(error, args[0]);
	p_strcat(error, "\n");

	free(hiStr);
	return (error);
}

/**
 * err_uno  function for the parv_alias error message
 *
 * Description:
 * @args: array arguments passed to command
 *
 * Return: string error
 */

char *err_uno(char **args)
{
	char *error;
	int length;

	length = p_strlent(name) + p_strlent(args[0]) + 13;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
		return (NULL);

	p_strcpy(error, "alias$ ");
	p_strcat(error, args[0]);
	p_strcat(error, " not found\n");

	return (error);
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
	char *error, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (NULL);

	args--;
	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(args[0]) + 45;
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
	p_strcat(error, ": Can't add or remove from environment\n");

	free(hiStr);
	return (error);
}
