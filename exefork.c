#include "p_shell.h"

/**
 * exec_command - creates a child process and execute a command
 *
 * Description:
 * @argument: arrays of srting rep command and argumnents
 * @strng: string pointer
 * @envi: environment variable
 *
 * Return: void
 *
 */

void exec_command(char **strng, char **argument, char *envi[])
{
	pid_t child_pid;
	int stats;
	char *err;
	char error_msg[] = "Fork issues";

	err = p_strcat(argument[0], "file or directory not found\n");

	child_pid = fork();
	if (child_pid < 0)
	{
		write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
		return;
	}
	if (child_pid == 0)
	{
		if (execve(strng[0], strng, envi) == -1)
		{
			write(STDERR_FILENO, err, p_strlent(err));
			exit(1);
		}
	}
	else
	{
		wait(&stats);
	}
}
