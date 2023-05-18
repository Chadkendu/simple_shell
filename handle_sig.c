#include "p_shell.h"

/**
 * handle_signal - handles the SIGNINT signal printing a new prompt
 *
 * Description:
 * @sign: signal number
 *
 * Return: void
 *
 */

void handle_signal(int sign)
{
	char *newPrompt = "cimba$ ";

	(void)sign; /** silence unused parameter warning **/
	sign(SIGINT, handle_signal); /** reinstall signal handler **/
	/** print new prompt **/
	write(STDIN_FILENO, newPrompt, 10);
}
