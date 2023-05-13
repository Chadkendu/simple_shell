#include "p_shell.h"

/**
 * handle_signal - handles the SIGNINT signal printing a new prompt
 *
 * Description:
 * @signal: signal number
 *
 * Return: void
 *
 */

void handle_signal(int signal)
{
	char *newPrompt = "\ncimba$ ";

	(void)signal; /** silence unused parameter warning **/
	signal(SIGINT, handle_signal); /** reinstall signal handler **/
	/** print new prompt **/
	write(STDIN_FILENO, newPrompt, strlen(newPrompt));
}
