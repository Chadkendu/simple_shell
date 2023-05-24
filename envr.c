#include "p_shell.h"

int parv_env(char **args, char __attribute__((__unused__)) **ahead);
int parv_unsetenv(char **args, char __attribute__((__unused__)) **ahead);
int parv_setenv(char **args, char __attribute__((__unused__)) **ahead);

char *name;
int hist_count;

/**
 * parv_setenv - Changes or adds environmental variable to PATH
 *
 * Description:
 * @args: array of arguments passed to shell
 * @ahead: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */

int parv_setenv(char **args, char __attribute__((__unused__)) **ahead)
{
	char **envirVar = NULL, **newEnviron, *newValue;
	size_t size;
	int inDex;

	if (!args[0] || !args[1])
		return (err_create(args, -1));

	newValue = malloc(p_strlent(args[0]) + 1 + p_strlent(args[1]) + 1);
	if (!newValue)
		return (err_create(args, -1));
	p_strcpy(newValue, args[0]);
	p_strcat(newValue, "=");
	p_strcat(newValue, args[1]);

	envirVar = p_getenv(args[0]);
	if (envirVar)
	{
		free(*envirVar);
		*envirVar = newValue;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * (size + 2));
	if (!newEnviron)
	{
		free(newValue);
		return (err_create(args, -1));
	}

	for (inDex = 0; environ[inDex]; inDex++)
		newEnviron[inDex] = environ[inDex];

	free(environ);
	environ = newEnviron;
	environ[inDex] = newValue;
	environ[inDex + 1] = NULL;

	return (0);
}

/**
 * parv_env - Prints the current environment status
 *
 * Description:
 * @args: array of arguments passed to shell.
 * @ahead: double pointer to the beginning of args
 *
 * Return: 0 (success), -1 (error).
 *
 */

int parv_env(char **args, char __attribute__((__unused__)) **ahead)
{
	int inDex;
	char new = '\n';

	if (!environ)
		return (-1);

	for (inDex = 0; environ[inDex]; inDex++)
	{
		write(STDOUT_FILENO, environ[inDex], p_strlent(environ[inDex]));
		write(STDOUT_FILENO, &new, 1);
	}
	(void)args;
	return (0);
}

/**
 * parv_unsetenv - Deletes environmental variable from PATH
 *
 * Description:
 * @args: array arguments passed to shell.
 * @ahead: double pointer to beginning of args
 *
 * Return: 0 (success), -1 (error)
 *
 */

int parv_unsetenv(char **args, char __attribute__((__unused__)) **ahead)
{
	char **envirVar, **newEnviron;
	size_t size;
	int inDex, inDexTwo;

	if (!args[0])
		return (err_create(args, -1));
	envirVar = p_getenv(args[0]);
	if (!envirVar)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * size);
	if (!newEnviron)
		return (err_create(args, -1));

	for (inDex = 0, inDexTwo = 0; environ[inDex]; inDex++)
	{
		if (*envirVar == environ[inDex])
		{
			free(*envirVar);
			continue;
		}
		newEnviron[inDexTwo] = environ[inDex];
		inDexTwo++;
	}
	free(environ);
	environ = newEnviron;
	environ[size - 1] = NULL;
	return (0);
}
