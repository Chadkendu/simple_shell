#include "p_shell.h"

/**
 * execute - Executes a command ( child process ).
 *
 * Description:
 * @args: array of arguments.
 * @ahead: double pointer at the beginning of args.
 *
 * Return:
 * error - if error occurs
 * else - exit value of last command
 *
 */

int execute(char **args, char **ahead)
{
	pid_t child_pid;
	int status, inval = 0, exitStat = 0;
	char *prompt = args[0];

	if (prompt[0] != '/' && prompt[0] != '.')
	{
		inval = 1;
		prompt = acq_location(prompt);
	} /** checks if prompt start with '/' or '.' **/

	if (!prompt || (access(prompt, F_OK) == -1))
	{
		if (errno == EACCES)
			exitStat = (err_create(args, 126));
		else
			exitStat = (err_create(args, 127));
	} /** if prompt not found or no permission **/
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (inval)
				free(prompt);
			perror("Invalid child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(prompt, args, envir);
			if (errno == EACCES)
				exitStat = (err_create(args, 126));
			env_free();
			args_free(args, ahead);
			alias_freelist(aliaz);
			_exit(exitStat);
		}
		else
			wait(&status);
			exitStat = WEXITSTATUS(status);
	}
	if (inval)
		free(prompt);
	return (exitStat);
}
