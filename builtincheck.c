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
	message = "inbuilt command.\n";
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
	message = "The environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "after a change of directory.\n";
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
	message = " exit 0.\n";
	write(STDOUT_FILENO, message, p_strlent(message));
}

/**
 * help_all - Displays all possible builtin parv command
 */

void help_all(void)
{
	char *message = "Parv commands are defined internally.\n";

	write(STDOUT_FILENO, message, p_strlent(message));
	message = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "out more about function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
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
	message = "Prints list of all aliases,;
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "the format NAME='VALUE' name [name2 ...]:prints";
	write(STDOUT_FILENO, message, _strlent(message));
	message = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "form NAME='VALUE'.alias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = " an alias f is given. If NAME ";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, message, p_strlent(message));
}
