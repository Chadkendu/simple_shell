#include "p_shell.h"

int err_create(char **args, int err);
int numb_len(int numb);
char *p_atoi(int numb);

/**
 * p_atoi - function to convert integer to a string
 *
 * Description:
 * @numb: number integer
 *
 * Return: converted string.
 */

char *p_atoi(int numb)
{
	char *buffer;
	int length = numb_len(numb);
	unsigned int numbOne;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (numb < 0)
	{
		numOne = numb * -1;
		buffer[0] = '-';
	}
	else
	{
		numOne = numb;
	}

	length--;
	do {
		buffer[length] = (numOne % 10) + '0';
		numOne /= 10;
		length--;
	} while (numOne > 0);

	return (buffer);
}

/**
 * numb_len - function to count digit length of a number
 *
 * Description:
 * @numb: number to measure
 *
 * Return: length of digit
 *
 */

int numb_len(int numb)
{
	unsigned int numOne;
	int length = 1;

	if (numb < 0)
	{
		length++;
		numOne = numb * -1;
	}
	else
	{
		numOne = numb;
	}
	while (numOne > 9)
	{
		length++;
		numOne /= 10;
	}

	return (length);
}

/**
 * err_create - custom error message to the STDERR
 *
 * Description:
 * @args: array of arguments.
 * @err: error value.
 *
 * Return: value of the error
 */

int err_create(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = err_env(args);
		break;
	case 1:
		error = err_uno(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = err_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = err_syntax(args);
		else
			error = err_cd(args);
		break;
	case 126:
		error = err_pa(args);
		break;
	case 127:
		error = err_rv(args);
		break;
	}
	write(STDERR_FILENO, error, p_strlent(error));

	if (error)
		free(error);
	return (err);
}
