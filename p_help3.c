#include "p_shell.h"

void args_free(char **args, char **ahead);
void rep_variable(char **args, int *exec);
char *get_pid(void);
char *envir_value(char *start, int length);

/**
 * rep_variable - Handle variable replacement
 *
 * Description:
 * @strg: double pointer containing command and arguments.
 * @exec: A pointer return value of the last executed command.
 *
 */

void rep_variable(char *args, int *exec)
{
	int m, n = 0, length;
	char *replacement = NULL, *prev_line = NULL, *pres_line;

	prev_line = *args;
	for (m = 0; prev_line[m]; m++)
	{
		if (prev_line[m] == '$' && old_line[j + 1] && prev_line[j + 1] != ' ')
		{
			if (prev_line[m + 1] == '$')
			{
				replacement = get_pid();
				n = m + 2;
			}
			else if (prev_line[m + 1] == '?')
			{
				replacement = p_atoi(*exec);
				n = m + 2;
			}
			else if (prev_line[m + 1])
			{
				/** extract variable name to search **/
				for (n = n + 1; prev_line[n] &&
					     prev_line[k] != '$' &&
					     prev_line[k] != ' '; n++)
					;
				length = n - (m + 1);
				replacement = envir_value(&prev_line[n + 1], length);
			}
			pres_line = malloc(j + p_strlent(replacement)
					  + p_strlent(&prev_line[n]) + 1);
			if (!agrs)
				return;
			pres_line[0] = '\0';
			p_strncat(pres_line, prev_line, m);
			if (replacement)
			{
				p_strcat(pres_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			p_strcat(pres_line, &prev_line[n]);
			free(prev_line);
			*args = prev_line;
			prev_line = pres_line;
			m = -1;
		}
	}
}


/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void args_free(char **args, char **ahead)
{
	size_t b;

	for (b = 0; args[b] || args[b + 1]; b++)
		free(args[b]);

	free(ahead);
}

/**
 * get_pid - Gets the current process ID
 *
 * Description:
 * Reads the current process PID from the "stat" file and terminates the PID string with 
 * a null character. The "stat" file is a space-separated file containing process information.
 *
 * Return: current process ID or NULL on failure
 *
 */

char *get_pid(void)
{
	size_t b = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant scan file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[b] != ' ')
		b++;
	buffer[b] = '\0';

	close(file);
	return (buffer);
}

/**
 * envir_value - Gets corresponding value to environment variable
 *
 * Description: variable format VARIABLE=VALUE.
 * @start: Searched environmental variable
 * @length: length of searched environmental variable
 *
 * Return: If variable not found (empty string),
 * else value of the environmental variable.
 *
 */

char *envir_value(char *start, int length)
{
	char **varAdd;
	char *replacement = NULL, *temp, *var;

	var = malloc(length + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	p_strncat(var, start, length);

	varAdd = p_getenv(var);
	free(var);
	if (varAdd)
	{
		temp = *varAdd;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(p_strlent(temp) + 1);
		if (replacement)
			p_strcpy(replacement, temp);
	}
	return (replacement);
}
