#include "p_shell.h"

int file_commandproc(char *filePath, int *exec);
int Xopen(char *filePath);

/**
 * file_commandproc - gets a file and runs a command
 *
 * Description:
 * @filePath: the files path
 * @exec: last command executed return value
 *
 * Return: file can't open (127)
 *   malloc failed (-1)
 *   else return value of the last executed command
 */

int file_commandproc(char *filePath, int *exec)
{
	ssize_t file, bScan, b;
	unsigned int lineSize = 0;
	unsigned int prev_size = 120;
	char *line, **args, **ahead;
	char buff[120];
	int exitStat;

	hist_count = 0;
	file = open(filePath, O_RDONLY);
	if (file == -1)
	{
		*exec = Xopen(filePath);
		return (*exec);
	}
	line = malloc(sizeof(char) * prev_size);
	if (!line)
		return (-1);
	do {
		bScan = read(file, buff, 119);
		if (bScan == 0 && lineSize == 0)
			return (*exec);
		buff[bScan] = '\0';
		lineSize += bScan;
		line = p_realloc(line, prev_size, lineSize);
		p_strcat(line, buff);
		prev_size = lineSize;
	} while (bScan);
	for (b = 0; line[b] == '\n'; b++)
		line[b] = ' ';
	for (; b < lineSize; b++)
	{
		if (line[b] == '\n')
		{
			line[b] = ';';
			for (b += 1; b < lineSize && line[b] == '\n'; b++)
				line[b] = ' ';
		}
	}
	rep_variable(&line, exec);
	handleLine(&line, lineSize);
	args = p_strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (args_check(args) != 0)
	{
		*exec = 2;
		args_free(args, args);
		return (*exec);
	}
	ahead = args;

	for (b = 0; args[b]; b++)
	{
		if (p_strncmp(args[b], ";", 1) == 0)
		{
			free(args[b]);
			args[b] = NULL;
			exitStat = args_call(args, ahead, exec);
			args = &args[++b];
			b = 0;
		}
	}

	exitStat = args_call(args, ahead, exec);

	free(ahead);
	return (exitStat);
}

/**
 * Xopen - function to check and print file errors
 *
 * Description:
 * @filePath: file path.
 *
 * Return: (127)
 */

int Xopen(char *filePath)
{
	char *erro, *hiStr;
	int length;

	hiStr = p_atoi(hist_count);
	if (!hiStr)
		return (127);

	length = p_strlent(name) + p_strlent(hiStr) + p_strlent(filePath) + 16;
	erro = malloc(sizeof(char) * (length + 1));
	if (!erro)
	{
		free(hiStr);
		return (127);
	}

	p_strcpy(erro, name);
	p_strcat(erro, ": ");
	p_strcat(erro, hiStr);
	p_strcat(erro, ": Invalid access ");
	p_strcat(erro, filePath);
	p_strcat(erro, "\n");

	free(hiStr);
	write(STDERR_FILENO, erro, length);
	free(erro);
	return (127);
}
