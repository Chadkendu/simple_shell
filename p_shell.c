#include "p_shell.h"

/**
 * main - entry point of the shell program
 *
 * Description:
 * This function reads the cmmnad line argument and exectute them
 * @argc: argument count
 * @argv: argument vector
 * @envi: environment variable
 *
 * Return: Always 0(success)
 *
 */

int main(int argc, char *argv[], char *envi[])
{
	char *line = NULL, *command_path; /**stores input string **/
	char **strng; /**stored parsed argumnets **/
	size_t w = 0, stats, bitm; /** initial buffer size **/
	ssize_t numb_char; /** stores num of character **/
	char *err_msg;/** terminal error message **/

	if (argc > 1)
		argv[1] = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "cimba$ ", 10);
		numb_char = p_getline(&line, &w, stdin); /**read user input **/
		if (numb_char == -1) /** check for errors **/
			free(line), exit(EXIT_FAILURE);

		if (*line != '\n') /** check for fork errors **/
		{
			strng = line_split(line);
			bitm = inbuilt_match(strng);
			err_msg = p_strcat(strng[0], "  not a valid command\n");
			command_path = generate_path(strng[0]);
			if (command_path)
			{
				strng[0] = command_path;
			}
			else
				stats = chkpath(strng[0]);

			if (stats == 1 || command_path)
				exec_command(strng, argv, envi);
			if (stats != 1 && !command_path && bitm == 0)
				write(STDERR_FILENO, err_msg, p_strlent(err_msg));
		}
	}
	free(line);
	free(strng);
	exit(0);
}
