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
	int exitStat = 0, exits;
	int *exec = &exits;
	char *prompt = "cimba$ ", *newLine = "\n";

	/** initailize global variable **/
	name = argv[0];
	hist_count = 1;
	aliaz = NULL;
	signal(SIGINT, handle_sig);

	*exec = 0;

	/** copy environment variable **/
	envir = p_copyenv();
	if (!envir)
		exit(-100);

	/** check for file commands **/
	if (argc != 1)
	{
		exitStat = file_commandproc(argv[1], exec);
		env_free();
		alias_freelist(alaiz);
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
		write(STDOUT_FILENO, prompt, 2);
		exitStat = args_handle(exec);
		if (exitStat == FILE_END || exitStat == EXIT)
		{
			if (exitStat = FILE_END)
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
