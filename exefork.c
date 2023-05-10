#include "p_shell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * exefork - creates a child process and execute a command
 *
 * Description:
 * @argument: arrays of srting rep command and argumnents
 *
 * Return: void
 *
 */

void exefork(char **argument)
{
	pid_t child_pid;
	int stats;
	char error_msg[] = "Fork issues";
	char err_msg[] = "[file or directory not found]\n";

	child_pid = fork();
	if (child_pid == -1)
	{
		write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
		return;
	}
	if (child_pid == 0)
	{
		if (execvp(argument[0], argument) == -1)
		{
			write(STDERR_FILENO, err_msg, sizeof(err_msg) - 1);
			exit(1);
		}
	}
	else
	{
		wait(&stats);
	}
}
