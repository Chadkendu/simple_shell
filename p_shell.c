#include "p_shell.h"

/**
 * main - entry point of the UNIX shell
 *
 * Description:
 * This function reads the cmmnad line argument and exectute them
 * @argc: argument count number
 * @argv: argument vector array
 *
 * Return: value of last command
 *
 */


int main(int argc, char *argv[])
{
	int exitStat = 0, exi;
	int *exec = &exi;
	char *prompt = "cimba$ ", *newLine = "\n";

	name = argv[0];
	hist_count = 1;
	aliaz = NULL;
	signal(SIGINT, sigHandler);
	*exec = 0;
	environ = p_copyenv();/** copy env var **/
	if (!environ)
		exit(-100);
	if (argc != 1)/** check file cmd **/
	{
		exitStat = file_commandproc(argv[1], exec);
		env_free();
		alias_freelist(aliaz);
		return (*exec);
	}
	if (!isatty(STDIN_FILENO))/** check non_int mode **/
	{
		while (exitStat != FILE_END && exitStat != EXIT)
			exitStat = args_handle(exec);
		env_free(), alias_freelist(aliaz);
		return (*exec);
	}
	while (1)/** interactive **/
	{
		write(STDOUT_FILENO, prompt, 10);
		exitStat = args_handle(exec);
		if (exitStat == FILE_END || exitStat == EXIT)
		{
			if (exitStat == FILE_END)
				write(STDOUT_FILENO, newLine, 1);
			env_free(), alias_freelist(aliaz);
			exit(*exec);
		}
	}
	env_free(), alias_freelist(aliaz);
	return (*exec);
}

/**
 * sigHandler - handles the SIGNINT signal printing a new prompt
 *
 * Description:
 * @sign: signal number
 *
 * Return: void
 *
 */

void sigHandler(int sign)
{
	char *newPrompt = "cimba$ ";

	(void)sign; /** silence unused parameter warning **/
	signal(SIGINT, sigHandler); /** reinstall signal handler **/
	/** print new prompt **/
	write(STDIN_FILENO, newPrompt, 10);
}


