#include "p_shell.h"

/**
 * parv - function that executes a command
 *
 * Description:
 * @arv: argument vector
 * @envr: environment vector
 *
 * Return: Always 0(success)
 *
 */

void parv(char **arv, char **envr)
{
	int stats;
	char *strng = NULL; /** input string pointer **/
	size_t w = 0; /** aloocated buffer size for input string **/
	ssize_t numb_char; /** no of char read by getline **/

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "cimba$ ", 10);

		/** reads a line input from stdin using getline **/
		numb_char = getline(&strng, &w, stdin);
		if (numb_char == -1)
		{
			free(strng);
			exit(EXIT_FAILURE);
		}

		/** remve trailing newline chars **/
		strng[p_strcspn(strng, '\n')] = 0;

		stats = check_command(strng, arv, envr);
		if (stats == -1)
			continue;
	}
	free(strng);
	exit(EXIT_SUCCESS);
}
