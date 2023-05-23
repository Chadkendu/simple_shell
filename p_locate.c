#include "p_shell.h"

char *acq_location(char *prompt);
link_t *getDirPath(char *path);
char *fillDirPath(char *path);

/**
 * getDirPath - Tokenize list of driectory into a linkedlist
 *
 * Description:
 * @path: The list of directories.
 *
 * Return: pointer to initialized linked list.
 */

link_t *getDirPath(char *path)
{
	int index;
	char **dirt, *pathCopy;
	link_t *top = NULL;

	/** create copy of path strng with (NULL) **/
	pathCopy = fillDirPath(path);
	if (!pathCopy)
		return (NULL);
	/** tokenize path string using colon delim **/
	dirt = p_strtok(pathCopy, ":");
	free(pathCopy);
	if (!dirt)
		return (NULL);
	/** add directory to linked list **/
	for (index = 0; dirt[index]; index++)
	{
		if (core_add(&top, dirt[index]) == NULL)
		{
			list_free(top);
			free(dirt);
			return (NULL);
		}
	}
	free(dirt);
	return (top);
}

/**
 * fillDirPath - Copies path and replace with directory and colons
 *
 * Description:
 * @path: The list of directories.
 *
 * Return: A copy of path
 *
 */

char *fillDirPath(char *path)
{
	int b, length = 0;
	char *pathCopy, *pwd;

	pwd = *(p_getenv("PWD")) + 4;/* get pwd */
	for (b = 0; path[b]; b++)
	{
		if (path[b] == ':')
		{
			if (path[b + 1] == ':' || b == 0 || path[b + 1] == '\0')
				length += p_strlent(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	} /** calculate string length **/
	pathCopy = malloc(sizeof(char) * (length + 1));
	if (!pathCopy)
		return (NULL);
	pathCopy[0] = '\0';
	for (b = 0; path[b]; b++)
	{
		if (path[b] == ':')
		{
			if (b == 0)
			{
				p_strcat(pathCopy, pwd);
				p_strcat(pathCopy, ":");
			}
			else if (path[b + 1] == ':' || path[b + 1] == '\0')
			{
				p_strcat(pathCopy, ":");
				p_strcat(pathCopy, pwd);
			}
			else
				p_strcat(pathCopy, ":");
		}
		else
		{
			p_strncat(pathCopy, &path[b], 1);
		}
	}
	return (pathCopy);
}

/**
 * acq_location - Locates command in PATH.
 *
 * Description:
 * @prompt: Command to locate.
 *
 * Return: (NULL) if error, (0) full pathname of command
 *
 */

char *acq_location(char *prompt)
{
	char **path, *temp;
	link_t *dirt, *top;
	struct stat srt;

	/** get env path value **/
	path = p_getenv("PATH");
	if (!path || !(*path))
		return (NULL);
	/** convert path string to linked list **/
	dirt = getDirPath(*path + 5);
	top = dirt;

	while (dirt)
	{
		temp = malloc(p_strlent(dirt->dir) + p_strlent(prompt) + 2);
		if (!temp)
			return (NULL);

		p_strcpy(temp, dirt->dir);
		p_strcat(temp, "/");
		p_strcat(temp, prompt);

		if (stat(temp, &srt) == 0)
		{
			list_free(top);
			return (temp);
		}

		dirt = dirt->nex;
		free(temp);
	}
	list_free(top);
	return (NULL);
}
