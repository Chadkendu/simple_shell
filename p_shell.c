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

int execute(char **args, char **ahead);
void handle_signal(int sign);

int main(int argc, char *argv[])
{
	int exitStat = 0, exi;
	int *exec = &exi;
	char *prompt = "cimba$ ", *newLine = "\n";

	/** initailize global variable **/
	name = argv[0];
	hist_count = 1;
	aliaz = NULL;
	signal(SIGINT, handle_signal);

	*exec = 0;

	/** copy environment variable **/
	environ = p_copyenv();
	if (!environ)
		exit(-100);

	/** check for file commands **/
	if (argc != 1)
	{
		exitStat = file_commandproc(argv[1], exec);
		env_free();
		alias_freelist(aliaz);
		return (*exec);
	}
	/** check for non-interactive mode **/
	if (!isatty(STDIN_FILENO))
	{
		while (exitStat != FILE_END && exitStat != EXIT)
			exitStat = args_handle(exec);
		env_free();
		alias_freelist(aliaz);
		return (*exec);
	}
	/** interactive mode **/
	while (1)
	{
		write(STDOUT_FILENO, prompt, 10);
		exitStat = args_handle(exec);
		if (exitStat == FILE_END || exitStat == EXIT)
		{
			if (exitStat == FILE_END)
				write(STDOUT_FILENO, newLine, 1);
			env_free();
			alias_freelist(aliaz);
			exit(*exec);
		}
	}
	env_free();
	alias_freelist(aliaz);
	return (*exec);
}

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
        signal(SIGINT, handle_signal); /** reinstall signal handler **/
        /** print new prompt **/
        write(STDIN_FILENO, newPrompt, 10);
}


