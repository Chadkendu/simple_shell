#include "p_shell.h"

int err_create(char **args, int erro);
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
	char *buff;
	int length = numb_len(numb);
	unsigned int numbOne;

	buff = malloc(sizeof(char) * (length + 1));
	if (!buff)
		return (NULL);

	buff[length] = '\0';

	if (numb < 0)
	{
		numbOne = numb * -1;
		buff[0] = '-';
	}
	else
	{
		numbOne = numb;
	}

	length--;
	do {
		buff[length] = (numbOne % 10) + '0';
		numbOne /= 10;
		length--;
	} while (numbOne > 0);

	return (buff);
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
	unsigned int numbOne;
	int length = 1;

	if (numb < 0)
	{
		length++;
		numbOne = numb * -1;
	}
	else
	{
		numbOne = numb;
	}
	while (numbOne > 9)
	{
		length++;
		numbOne /= 10;
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

int err_create(char **args, int erro)
{
	char *error;

	switch (erro)
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
	return (erro);
}
