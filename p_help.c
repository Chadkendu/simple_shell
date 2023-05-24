#include "p_shell.h"

int args_check(char **args);
char *args_acq(char *line, int *exec);
int args_handle(int *exec);
int args_run(char **args, char **ahead, int *exec);
int args_call(char **args, char **ahead, int *exec);

char *name;
int hist_count;

/**
 * args_call - Partitions operators from commands and calls them
 *
 * Description:
 * @args: array of arguments
 * @ahead: double pointer to the beginning of args
 * @exec: return value of the parent process (last executed command)
 *
 * Return: The value of last executed command
 *
 */

int args_call(char **args, char **ahead, int *exec)
{
	int exitStat, inDex;

	if (!args[0])
		return (*exec);
	for (inDex = 0; args[inDex]; inDex++)
	{
		if (p_strncmp(args[inDex], "||", 2) == 0)
		{
			free(args[inDex]);
			args[inDex] = NULL;
			args = alias_replace(args);
			exitStat = args_run(args, ahead, exec);
			if (*exec != 0)
			{
				args = &args[++inDex];
				inDex = 0;
			}
			else
			{
				for (inDex++; args[inDex]; inDex++)
					free(args[inDex]);
				return (exitStat);
			}
		}
		else if (p_strncmp(args[inDex], "&&", 2) == 0)
		{
			free(args[inDex]);
			args[inDex] = NULL;
			args = alias_replace(args);
			exitStat = args_run(args, ahead, exec);
			if (*exec == 0)
			{
				args = &args[++inDex];
				inDex = 0;
			}
			else
			{
				for (inDex++; args[inDex]; inDex++)
					free(args[inDex]);
				return (exitStat);
			}
		}
	}
	args = alias_replace(args);
	exitStat = args_run(args, ahead, exec);
	return (exitStat);
}

/**
 * args_acq - Get  command from stdin
 *
 * Description:
 * @line: A buffer to store the command.
 * @exec: return value of the last command executed
 *
 * Return: error occurs - NULL.
 *         else - pointer to the command stored
 */

char *args_acq(char *line, int *exec)
{
	size_t w = 0;
	ssize_t read;
	char *prompt = "cimba$ ";

	if (line)
		free(line);

	read = p_getline(&line, &w, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist_count++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (args_acq(line, exec));
	}

	line[read - 1] = '\0';
	rep_variable(&line, exec);
	handleLine(&line, read);

	return (line);
}

/**
 * args_check - Check if there are leading ';', ';;', '&&', or '||'
 *
 * Description:
 * @args: pointer to tokenized command and argument
 *
 * Return: If a ';', '&&', or '||' placed at invalid position (2)
 * Otherwise (0).
 */

int args_check(char **args)
{
	size_t b;
	char *current, *next;

	for (b = 0; args[b]; b++)
	{
		current = args[b];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (b == 0 || current[1] == ';')
				return (err_create(&args[b], 2));
			next = args[b + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (err_create(&args[b + 1], 2));
		}
	}
	return (0);
}

/**
 * args_handle - Call, run, and gets the command execution
 *
 * Description:
 * @exec: return value of the parent process (last executed command)
 *
 * Return: If an end of file is scanned - FILE_END (-2)
 *         If input can't be tokenized (-1)
 *         O/w - exit value of the last command executed
 *
 */

int args_handle(int *exec)
{
	int exitStat = 0, index;
	char **args, *line = NULL, **ahead;

	line = args_acq(line, exec);
	if (!line)
		return (FILE_END);

	args = p_strtok(line, " ");
	free(line);
	if (!args)
		return (exitStat);
	if (args_check(args) != 0)
	{
		*exec = 2;
		args_free(args, args);
		return (*exec);
	}
	ahead = args;

	for (index = 0; args[index]; index++)
	{
		if (p_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			exitStat = args_call(args, ahead, exec);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		exitStat = args_call(args, ahead, exec);

	free(ahead);
	return (exitStat);
}

/**
 * args_run - Calls execution of a command
 *
 * Description:
 * @args: array of arguments.
 * @ahead: double pointer to args beginning
 * @exec: return value of the parent process (last executed command)
 *
 * Return: the return value of the command executed last
 *
 */

int args_run(char **args, char **ahead, int *exec)
{
	int exitStat, b;
	int (*inbuilt)(char **args, char **ahead);

	inbuilt = inbuilt_get(args[0]);

	if (inbuilt)
	{
		exitStat = inbuilt(args + 1, ahead);
		if (exitStat != EXIT)
			*exec = exitStat;
	}
	else
	{
		*exec = execute(args, ahead);
		exitStat = *exec;
	}

	hist_count++;

	for (b = 0; args[b]; b++)
		free(args[b]);

	return (exitStat);
}
