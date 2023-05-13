#include "p_shell.h"

/**
 * generate_path - function that generate path
 *
 * Description:
 * @command: compare and construct full path
 *
 * Return: void
 *
 */

char *generate_path(char *command)
{
	DIR *directory = opendir("/bin/");
	char *temp_str, *command_path;
	struct dirent *dir_entry;

	if (!directory)
		return (NULL);

	dir_entry = readdir(directory);

	while (dir_entry)
	{
		temp_str = dir_entry->d_name; /** set temp string to directory entry name **/
		if (p_strcmp(temp_str, command) == 0) /** compares temp string to command **/
		{
			command_path = p_strcat("/bin/", command);
			closedir(directory);
			return (command_path);
		}
		dir_entry = readdir(directory); /** reads next directory entry **/
	}
	closedir(directory);
	return (NULL);
}
