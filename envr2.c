#include "p_shell.h"

char **p_getenv(const char *var);
char **p_copyenv(void);
void env_free(void);

/**
 * free_env - Function to free copy of the environment
 *
 * Return: void
 */

void env_free(void)
{
	int index;

	for (index = 0; envir[index]; index++)
		free(envir[index]);
	free(envir);
}

/**
 * p_getenv - Get the environment variable from PATH
 *
 * Description:
 * @var: environmental variable to get
 *
 * Return: environmental variable does not exist (NULL)
 *         else pointer to the environmental variable.
 */

char **p_getenv(const char *var)
{
	int index, length;

	length = p_strlent(var);
	for (index = 0; envir[index]; index++)
	{
		if (p_strncmp(var, envir[index], length) == 0)
			return (&envir[index]);
	}

	return (NULL);
}

/**
 * p_copyenv - Creates environment copy
 *
 * Description: void
 *
 * Return: If an error occurs - NULL.
 *         else double pointer to new copy.
 */

char **p_copyenv(void)
{
	char **newEnviron;
	size_t size;
	int index;

	for (size = 0; envir[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * (size + 1));
	if (!newEnviron)
		return (NULL);

	for (index = 0; envir[index]; index++)
	{
		newEnviron[index] = malloc(p_strlent(envir[index]) + 1);

		if (!newEnviron[index])
		{
			for (index--; index >= 0; index--)
				free(newEnviron[index]);
			free(newEnviron);
			return (NULL);
		}
		p_strcpy(newEnviron[index], envir[index]);
	}
	newEnviron[index] = NULL;
	return (newEnviron);
}
