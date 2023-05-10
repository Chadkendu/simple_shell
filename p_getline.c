#include "p_shell.h"

/**
 * p_getline - reads the line from a stream
 *
 * Description:
 * @lneptr: address of a pointer to the buffer to stre line
 * @w: pointer to the buffer size
 * @strm: the stream to read from
 *
 * Return: the number of character read (0), or failed (1)
 *
 */

ssize_t p_getline(char **lneptr, size_t *w, FILE *strm)
{
	char strg[120]; /** declares a buffer to hold temporary input data **/

	if (lneptr == NULL || w == NULL || strm == NULL)
	{
		perror("invalid parameters");
		exit(EXIT_FAILURE);
	} /** checks for invalid parameters **/
	if (*lneptr == NULL)
	{
		*lneptr = malloc(sizeof(strg));
		if (*lneptr == NULL)
		{
			perror("Can't allocate memory");
			exit(EXIT_FAILURE);
		}
	} /** allocates memory for the buffer to stroe input data **/
	*lneptr[0] = '\0'; /**initialize firat element of the buffer to null **/
	while (fgets(*lneptr, *w, strm)) /** reads data from stream till newline
					  * char if found or end of line is reached **/
	{
		if ((*w - strlen(*lneptr)) < sizeof(strg))
		{
			*w *= 2;
			*lneptr = realloc(*lneptr, *w);
			if (*lneptr == NULL)
			{
				perror("Can't allocate space");
				exit(EXIT_FAILURE);
			} /** to reasize the buffer if large **/
		}
		strcat(*lneptr, strg); /**append input data to buffer **/
		if ((*lneptr)[strlen(*lneptr) - 1] == '\n')
		{
			return (strlen(*lneptr));
		}
	}
	return (0);
}
