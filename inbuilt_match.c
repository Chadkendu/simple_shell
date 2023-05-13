#include "p_shell.h"

/**
 * inbuilt_match - function to match inbuilt command
 *
 * Description:
 * This function searches for command in a static array of inbuilt_t struct
 * which associate command names with corresponding function pointers
 * if the match if found, we call the corresponding function
 * with command argument and result is returned
 * @commands: inbuilt command(with argument)
 *
 * Return: 0(failed)
 *
 */

size_t inbuilt_match(char **commands)
{
	int b = 0;

	/**
	 * define static array of inbuilt_struct, the last struct has NUll
	 * value indicating the end of array **/
	inbuilt_t match[] = {
		{"setenv", p_setenv},
		{"exit", p_exit},
		{NULL, NULL},
	};
	while (match[b].command)
	{
		if (p_strcmp(match[b].command, commands[0]) == 0)
			return (match[b].f_ptr(commands));
		b++;
	}
	return (0);
}
