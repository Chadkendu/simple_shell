#include "p_shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);

/**
 * help_unsetenv - Displays information on the parv command
 *
 */

void help_unsetenv(void)
{
	char *message = "unsetenv [VARIABLE]";

	write(STDOUT_FILENO, message, p_strlent(message));
	message = "environmental variable";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "stderr message.\n";
	write(STDOUT_FILENO, message, p_strlent(message));
}

/**
 * help_env - Displays information on the parv command
 */

void help_env(void)
{
	char *message = "env: diesplay the current environment.\n";

	write(STDOUT_FILENO, message, p_strlent(message));
}

/**
 * help_setenv - Displays information on the parv command
 */

void help_setenv(void)
{
	char *message = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, message, p_strlent(message));
	message = "environment variable\n";
	write(STDOUT_FILENO, message, p_strlent(message));
	message = "Failed: display message to stderr.\n";
	write(STDOUT_FILENO, message, p_strlent(message));
}
