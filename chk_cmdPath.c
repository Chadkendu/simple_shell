#include "p_shell.h"

/**
 * check_cmdpath - function to check if string is valid within /bin/
 *
 * Description:
 * @command: pointer to the string
 *
 * Return: void
 *
 */

int check_cmdpath(char *command)
{
	char *prefix = "/bin/", *path_ptr, *temp_ptr;
	int prefix_index = 0, path_index = 0;

	path_ptr = malloc(sizeof(char) * MAX_ARGS); /** allocate memory cmdpath **/
	if (!path_ptr)
	{
		free(path_ptr);
		return (0);
	}
	while (prefix[prefix_index] != '\0')
	{
		if (prefix[prefix_index] != command[prefix_index])
		{
			free(path_ptr);
			return (0);
		}
		prefix_index++;
	}
	while (command[prefix_index] != '\0')
	{
		path_ptr[path_index] = command[prefix_index], path_index++, prefix_index++;
	}
	path_ptr[path_index] = '\0'; /** add null terminator to string path **/
	temp_ptr = generate_path(path_ptr);
	if (temp_ptr)
	{
		free(path_ptr);
		return (1);
	}
	return (0);
}
