#include "p_shell.h"

void args_free(char **args, char **ahead);
void rep_variable(char **args, int *exec);
char *get_pid(void);
char *envir_value(char *start, int length);

/**
 * rep_variable - Handle variable replacement
 *
 * Description:
 * @args: double pointer containing command and arguments.
 * @exec: A pointer return value of the last executed command.
 *
 */

void rep_variable(char **line, int *exec)
{
	int m, n = 0, length;
	char *replace = NULL, *prev_line = NULL, *pres_line;

	prev_line = *line;
	for (m = 0; prev_line[m]; m++)
	{
		if (prev_line[m] == '$' && prev_line[n + 1] && prev_line[n + 1] != ' ')
		{
			if (prev_line[m + 1] == '$')
			{
				replace = get_pid();
				n = m + 2;
			}
			else if (prev_line[m + 1] == '?')
			{
				replace = p_atoi(*exec);
				n = m + 2;
			}
			else if (prev_line[m + 1])
			{
				for (n = n + 1; prev_line[n] &&
					     prev_line[m] != '$' &&
					     prev_line[m] != ' '; n++)
					;
				length = n - (m + 1);
				replace = envir_value(&prev_line[n + 1], length);
			}
			pres_line = malloc(n + p_strlent(replace)
					  + p_strlent(&prev_line[n]) + 1);
			if (!line)
				return;
			pres_line[0] = '\0';
			p_strncat(pres_line, prev_line, m);
			if (replace)
			{
				p_strcat(pres_line, replace);
				free(replace);
				replace = NULL;
			}
			p_strcat(pres_line, &prev_line[n]);
			free(prev_line);
			*line = pres_line;
			prev_line = pres_line;
			m = -1;
		}
	}
}


/**
 * args_free - Frees up memory taken by args.
 *
 * Description:
 * @args: A null-terminated double pointer containing commands/arguments.
 * @ahead: A double pointer to the beginning of args.
 *
 * Return: void
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
 * Reads the current process PID from the "stat" file
 * and terminates the PID string with
 * a null character. The "stat" file is a space-separated
 * file containing process information.
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
	char *replace = NULL, *temp, *variable;

	variable = malloc(length + 1);
	if (!variable)
		return (NULL);
	variable[0] = '\0';
	p_strncat(variable, start, length);

	varAdd = p_getenv(variable);
	free(variable);
	if (varAdd)
	{
		temp = *varAdd;
		while (*temp != '=')
			temp++;
		temp++;
		replace = malloc(p_strlent(temp) + 1);
		if (replace)
			p_strcpy(replace, temp);
	}
	return (replace);
}
