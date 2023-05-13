#include "p_shell.h"

/**
 * line_split - tokenize a string
 *
 * Description:
 * @command_string: string parameter(command from termianl)
 *
 * Return: Array of string
 *
 */

char **line_split(char *command_string)
{
	char **token_array, *current_token;
	int token_count = 0, char_index = 0;

	token_array = malloc(MAX_ARGS * sizeof(char *));
	if (token_array == NULL)
		perror("Can't allocate memory\n"), exit(EXIT_FAILURE);

	/** eliminate newline character **/
	while (command_string[char_index])
	{
		if (command_string[char_index] == '\n')
			command_string[char_index] = '\0';
		char_index++;
	}
	/** tokenize **/
	current_token = strtok(command_string, " ");
	while (current_token != NULL)
	{
		token_array[token_count] = current_token;
		token_count++;
		current_token = strtok(NULL, " ");
	}
	token_array[token_count] = NULL; /** indicate end of array **/
	return (token_array);
}
