#include "p_shell.h"

int parv_env(char **args, char __attribute__((__unused__)) **ahead);
int parv_unsetenv(char **args, char __attribute__((__unused__)) **ahead);
int parv_setenv(char *8args, char __attribute__((__unused__)) **ahead);

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
	int index;

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
	for (size = 0; envir[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * (size + 2));
	if (!newEnviron)
	{
		free(newValue);
		return (err_create(args, -1));
	}

	for (index = 0; envir[index]; index++)
		newEnviron[index] = envir[index];

	free(envir);
	envir = newEnviron;
	envir[index] = newValue;
	envir[index + 1] = NULL;

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
	int index;
	char new = '\n';

	if (!envir)
		return (-1);

	for (index = 0; envir[index]; index++)
	{
		write(STDOUT_FILENO, envir[index], p_strlent(envir[index]));
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
 * @front: double pointer to beginning of args
 *
 * Return: 0 (success), -1 (error)
 *
 */

int parv_unsetenv(char **args, char __attribute__((__unused__)) **ahead)
{
	char **envirVar, **newEnviron;
	size_t size;
	int index, indexTwo;

	if (!args[0])
		return (err_create(args, -1));
	envirVar = p_getenv(args[0]);
	if (!envirVar)
		return (0);

	for (size = 0; envir[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * size);
	if (!newEnviron)
		return (err_create(args, -1));

	for (index = 0, indexTwo = 0; envir[index]; index++)
	{
		if (*envirVar == envir[index])
		{
			free(*envirVar);
			continue;
		}
		newEnviron[indexTwo] = envir[index];
		indexTwo++;
	}
	free(envir);
	envir = newEnviron;
	envir[size - 1] = NULL;
	return (0);
}
