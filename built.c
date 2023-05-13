#include "p_shell.h"

int (*inbuilt_get(char *command))(char **args, char **ahead);
int parv_exit(char **args, char **ahead);
int parv_cd(char **args, char __attribute__((__unused__)) **ahead);
int parv_help(char **args, char __attribute__((__unused__)) **ahead);

/**
 * parv_help - Displays information about parv commands
 *
 * Description:
 * @args: array of arguments.
 * @ahead: pointer to args beginning
 *
 * Return: 0 (success), -1 (error)
 */

int parv_help(char **args, char __attribute__((__unused__)) **ahead)
{
	if (!args[0])
		help_all();
	else if (p_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (p_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (p_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (p_strcmp(args[0], "env") == 0)
		help_env();
	else if (p_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (p_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (p_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, p_strlent(name));

	return (0);
}

/**
 * parv_cd - Changes the current directory
 *
 * Description:
 * @args: array of arguments
 * @ahead: double pointer to args beginning
 *
 * Return: string not a directory (2)
 * error occurs (-1), 0 (success)
 */

int parv_cd(char **args, char __attribute__((__unused__)) **ahead)
{
	char **dirInfo, *newLine = "\n";
	char *prev_pwd = NULL, *pwd = NULL;
	struct stat dirc;

	prev_pwd = getcwd(prev_pwd, 0);
	if (!prev_pwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || p_strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
			    args[0][1] == '\0')
			{
				if (p_getenv("OLDPWD") != NULL)
					(chdir(*p_getenv("OLDPWD") + 7));
			}
			else
			{
				free(prev_pwd);
				return (err_create(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dirc) == 0 && S_ISDIR(dirc.st_mode)
			    && ((dirc.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(prev_pwd);
				return (err_create(args, 2));
			}
		}
	}
	else
	{
		if (p_getenv("HOME") != NULL)
			chdir(*(p_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dirInfo = malloc(sizeof(char *) * 2);
	if (!dirInfo)
		return (-1);

	dirInfo[0] = "OLDPWD";
	dirInfo[1] = prev_pwd;
	if (parv_setenv(dirInfo, dirInfo) == -1)
		return (-1);

	dirInfo[0] = "PWD";
	dirInfo[1] = pwd;
	if (parv_setenv(dirInfo, dirInfo) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, P_strlent(pwd));
		write(STDOUT_FILENO, newLine, 1);
	}
	free(prev_pwd);
	free(pwd);
	free(dirInfo);
	return (0);
}

/**
 * inbuilt_get - Matches a command with parv inbuilt
 *
 * Description:
 * @command: The command matched
 *
 * Return: function pointer to the corresponding inbuilt
 */

int (*inbuilt_get(char *command))(char **args, char **ahead)
{
	inbuilt_t funct[] = {
		{ "exit", parv_exit },
		{ "env", parv_env },
		{ "setenv", parv_setenv },
		{ "unsetenv", parv_unsetenv },
		{ "cd", parv_cd },
		{ "alias", parv_alias },
		{ "help", parv_help },
		{ NULL, NULL }
	};
	int b;

	for (b = 0; funct[b].name; b++)
	{
		if (p_strcmp(funct[b].name, command) == 0)
			break;
	}
	return (funct[b].f);
}

/**
 * parv_exit - Causes process termination
 *
 * Description:
 * @args: array of arguments with exit value
 * @ahead: double pointer to args beginning
 *
 * Return: no arguments (-3)
 * exit value is invalid (2)
 * else exits with given status value
 *
 */

int parv_exit(char **args, char **ahead)
{
	int b, lenOfInt = 10;
	unsigned int numb = 0, maxim = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			b = 1;
			lenOfInt++;
		}
		for (; args[0][b]; b++)
		{
			if (b <= lenOfInt && args[0][b] >= '0' && args[0][b] <= '9')
				numb = (numb * 10) + (args[0][b] - '0');
			else
				return (err_create(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (numb > maxim - 1)
		return (err_create(--args, 2));
	args -= 1;
	args_free(args, ahead);
	env_free();
	alias_freelist(aliaz);
	exit(numb);
}
