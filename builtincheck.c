#include "p_shell.h"

void help_cd(void);
void help_all(void);
void help_exit(void);
void help_alias(void);
void help_help(void);

/**
 * help_help - Displays information on the parv command
 */

void help_help(void)
{
	char *message = "help: See all possible parv inbuilt commands.\n";

	write(STDOUT_FILENO, message, p_strlent(message));
	message = "help [BUILTIN NAME] ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "builtin command.\n";
	write(STDOUT_FILENO, message, p_strlent(message));
}

/**
 * help_cd - Displays information on the parv command
 */

void help_cd(void)
{
	char *message = "cd: cd [DIRECTORY]";

	write(STDOUT_FILENO, message, p_strlent(message));
	message = " process to DIRECTORY\n";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "command is interpreted as cd HOME\n";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = " given, the command is interpreted  cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "Environment variables PWD and OLDPWD updated ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "after a directory change.\n";
	write(STDOUT_FILENO, message, p_strlent(message));
}

/**
 * help_exit - displays info on the parv command line
 */

void help_exit(void)
{
	char *message = "exit: exit [STATUS]";

	write(STDOUT_FILENO, message, p_strlent(message));
	message = "to exit the shell.";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = " If no argument  the command is interpreted as";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = " exit 0(success).\n";
	write(STDOUT_FILENO, message, p_strlent(message));
}

/**
 * help_all - Displays all possible builtin parv command
 */

void help_all(void)
{
	char *message = "Parv commands are defined internally.\n";

	write(STDOUT_FILENO, message, p_strlent(message));
	message = "Type 'help' to see this list.Type 'help name' to find ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "out more about function 'name'.\nalias\t";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "alias [NAME[='VALUE'] ...]  cd\tcd   ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "[DIRECTORY]\n exit [STATUS]\n  env\tenv";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "\nsetenv setenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, message, p_strlent(message));
}

/**
 * help_alias - Displays information on the parv command
 */

void help_alias(void)
{
	char *message = "alias: alias [NAME[='VALUE']\n";

	write(STDOUT_FILENO, message, p_strlent(message));
	message = "Prints all aliases list to the terminal";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = " :prints";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = " the aliases ene per line, in the ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "form E'.alias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = " an lias fis given. If NAME ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "is alr an aliah VALUE.\n";
	write(STDOUT_FILENO, message, p_strlent(message));
}
