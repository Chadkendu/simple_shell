#include "p_shell.h"

/**
 * p_getline - function to read input from stream
 *
 * Description:
 * @lneptr: buffer to store input received
 * @w: lneptr size
 * @strm: read stream
 *
 * Return: read bytes (number)
 */

void *p_realloc(void *ptr, unsigned int prev_size, unsigned int pres_size);
void assLineptr(char **lneptr, size_t *w, char *buffer, size_t bSize);
ssize_t p_getline(char **lneptr, size_t *w, FILE *strm);

ssize_t p_getline(char **lneptr, size_t *w, FILE *strm)
{
	static ssize_t input;
	ssize_t exitStat;
	char k = 'x', *buffer;
	int v;

	if (input == 0)
		fflush(strm);
	else
		return (-1);
	input = 0;
	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (k != '\n')
	{
		v = read(STDIN_FILENO, &k, 1);
		if (v == -1 || (v == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (v == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buffer = p_realloc(buffer, input, input + 1);

		buffer[input] = k;
		input++;
	}
	buffer[input] = '\0';

	assLineptr(lneptr, w, buffer, input);

	exitStat = input;
	if (v != 0)
		input = 0;
	return (exitStat);
}

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

void assLineptr(char *lneptr, size_t *w, char *buffer, size_t bSize)
{
	if (*lneptr == NULL)
	{
		if (bSize > 120)
			*w = bSize;
		else
			*w = 120;
		*lneptr = buffer;
	}
	else if (*w < bSize)
	{
		if (bSize > 120)
			*w = bSize;
		else
			*w = 120;
		*lneptr = buffer;
	}
	else
	{
		p_strcpy(*lneptr, buffer);
		free(buffer);
	}
}

/**
 * p_realloc - Reallocate block memory with malloc and free
 *
 * Description:
 * @ptr: pointer to past allocated memory
 * @prev_size: The size in bytes of ptr space
 * @pres_size: new memory block bytes size
 *
 * Return: pres_size == prev_size (ptr)
 * pres_size == 0 && ptr not NULL (NULL)
 * else pointer to reallocated memory block
 *
 */

void *p_realloc(void *ptr, unsigned int prev_size, unsigned int pres_size)
{
	void *memory;
	char *ptrCopy, *fill;
	unsigned int index;

	if (pres_size == prev_size)
		return (ptr);

	if (ptr == NULL)
	{
		memory = malloc(pres_size);
		if (memory == NULL)
			return (NULL);

		return (NULL);
	}

	if (pres_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	
	ptrCopy = ptr;
	memory = malloc(sizeof(*ptrCopy) * pres_size);
	if (memory == NULL)
	{
		free(ptr);
		return (NULL);
	}

	fill = memory;

	for (index = 0; index < prev_size && index < pres_size; index++)
		fill[index] = *ptrCopy++;

	free(ptr);
	return (memory);
}
