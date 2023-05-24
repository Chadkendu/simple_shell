#include "p_shell.h"

char **p_getenv(const char *var);
char **p_copyenv(void);
void env_free(void);

char *name;
int hist_count;

/**
 * env_free - Function to free copy of the environment
 *
 * Return: void
 */

void env_free(void)
{
	int inDex;

	for (inDex = 0; environ[inDex]; inDex++)
		free(environ[inDex]);
	free(environ);
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
	int inDex, length;

	length = p_strlent(var);
	for (inDex = 0; environ[inDex]; inDex++)
	{
		if (p_strncmp(var, environ[inDex], length) == 0)
			return (&environ[inDex]);
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
	int inDex;

	for (size = 0; environ[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * (size + 1));
	if (!newEnviron)
		return (NULL);

	for (inDex = 0; environ[inDex]; inDex++)
	{
		newEnviron[inDex] = malloc(p_strlent(environ[inDex]) + 1);

		if (!newEnviron[inDex])
		{
			for (inDex--; inDex >= 0; inDex--)
				free(newEnviron[inDex]);
			free(newEnviron);
			return (NULL);
		}
		p_strcpy(newEnviron[inDex], environ[inDex]);
	}
	newEnviron[inDex] = NULL;
	return (newEnviron);
}
