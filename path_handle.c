#include "p_shell.h"

/**
 * check_command - checks if command exists in path
 *
 * Description:
 * @command: command string to search
 * @arguments: argument pointer
 * @environment: envrionment variable
 *
 * Return: 0(int) if found, -1 (if not found)
 *
 */

int check_command(char *command, char **arguments, char **environment)
{
	char *envr_path = getenv("PATH");
	char *dirc = strtok(envr_path, ":"), *argv[MAX_ARGS];
	char *path_full;
	int b = 0, lent;

	argv[0] = strtok(command, " ");
	while (argv[b])
		argv[++b] = strtok(NULL, " ");

	while (dirc)
	{
		lent = p_strlent(envr_path) + p_strlent(dirc);
		path_full = malloc(lent);
		if (!path_full)
			return (-1);

		strcpy(path_full, dirc);
		strcat(path_full, "/");
		strcat(path_full, argv[0]);

		if (access(path_full, X_OK) == 0)
		{
			command_exect(path_full, argv, arguments, environment);
			free(path_full);
			return (0);
		}
		free(path_full);
		dirc = strtok(NULL, ":");
	}
	printf("%s command invalid\n", argv[0]);
	return (-1);
}

/**
 * command_exect - finction to execute command
 *
 * Description:
 * @command: pointer to executed command
 * @argv: argument vector to command
 * @arv: argument array to string that rep env variable
 * @envr: environment variable to command
 *
 * Return: void
 *
 */

void command_exect(char *command, char *argv[], char **arv, char **envr)
{
	pid_t child_pid;
	int stats = 0;

	child_pid = fork();
	if (child_pid == -1)
	{
		free(command);
		exit(0);
	}
	if (child_pid == 0)
	{
		if (execve(command, argv, envr) == -1)
		{
			printf("%s: file or directory not found\n", arv[0]);
		}
	}
	else
	{
		wait(&stats);
	}
}
