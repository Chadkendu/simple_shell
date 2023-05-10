#include "p_shell.h"

/**
 * main - entry point of the shell program
 *
 * Description:
 * @arc: argument count
 * @arv: argument vector
 * @envr: environment vector
 *
 * Return: Always 0(success)
 *
 */

int main(int arc, char **arv, char **envr)
{
	if (arc == 1)
	{
		parv(arv, envr);
	}
	return (0);
}
