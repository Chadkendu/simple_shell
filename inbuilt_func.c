#include "p_shell.h"

/**
 * p_exit - terminate the process
 *
 * Description:
 * @command: command recieved from terminal
 *
 * Return: 0(if not found)
 *
 */

size_t p_exit(char **command)
{
	/** check if there is no command argument **/
	if (!command[1])
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		/** if exist, convert the arg to int **/
		int exit_code = p_atoi(command[1]);

		exit(exit_code);
	}
	return (0);
}

/**
 * p_setenv - add or change environment variable
 *
 * Description:
 * @strg: string of array containing variable vale or name
 *
 * Return: 0(failed)
 *
 */

size_t p_setenv(char **strg)
{
	int arg_count = 0;/** var to count arg number **/
	char *var_name;
	char *var_value;

	/** loop throught until NULL terminator is reached **/
	for (; strg[arg_count]; arg_count++)
		;
	if (arg_count == 3)
	{
		var_name = strg[1];
		var_value = strg[2];
		if (var_name && var_value)
			return (1);
	}
	return (0);
}
