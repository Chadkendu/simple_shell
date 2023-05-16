#include "p_shell.h"

/**
 * assLineptr - Reassign lineptr variable for p_getline function
 *
 * Description:
 * @lneptr: stored input string buffer
 * @w: lneptr size
 * @bSize: buffer size
 * @buff: assigned string ti lneptr
 *
 * Return: void
 *
 */

void *p_realloc(void *ptr, unsigned int prev_size, unsigned int pres_size);
void assLineptr(char **lneptr, size_t *w, char *buffer, size_t bSize);
ssize_t p_getline(char **lneptr, size_t *w, FILE *strm);
int limstrg(char *instr);

ssize_t p_getline(char **lneptr, size_t *w, FILE *strm)
{
	size_t strg = 120; /** declares a buffer to hold temporary input data **/
	size_t *strglen = &strg, n;

	if (!(isatty(STDIN_FILENO)))
		printf("\n");
	if (lneptr == NULL || w == NULL || strm == NULL)
	{
		perror("invalid parameters"), exit(EXIT_FAILURE);
	} /** checks for invalid parameters **/
	if (*lneptr == NULL)
	{
		*lneptr = malloc(sizeof(char) * (*strglen));
		if (*lneptr == NULL)
		{
			perror("Can't allocate memory"), exit(EXIT_FAILURE);
		}
	} /** allocates memory for the buffer to stroe input data **/
	else
		*lneptr = realloc(*lneptr, *strglen);
	while (1)
	{
		*lneptr = fgets(*lneptr, *strglen, strm);
		n = limstrg(*lneptr);
		if (n > (*strglen - 10))
		{
			*strglen = (*strglen) * 2;
			*lneptr = realloc(*lneptr, *strglen);
			if (*lneptr == NULL)
				exit(1);
		}
		if (n < (*strglen - 10))
			break;
	}
	if (n < (*strglen - 10))
	{
		*lneptr = realloc(*lneptr, n + 1);
		if (*lneptr == NULL)
			exit(0);
		*w = limstrg(*lneptr);
		return (1);
	}
	return (-1);
}

/**
 * limstrg - takes pointer to array and return int
 *
 * Description:
 * @instr: input string
 *
 * Return: void
 *
 */

int limstrg(char *instr)
{
	int length = 0;

	while (instr[length] != '\n')
	{
		length++;
	}
	length++;
	return (length);
}
