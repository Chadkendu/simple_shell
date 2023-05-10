#include "p_shell.h"

/**
 * main - entry point of the shell program
 *
 * Description:
 * This function reads the cmmnad line argument and exectute them
 *
 * Return: Always 0(success)
 *
 */

int main(void)
{
	char *ptr; /**stores input string **/
	char **strng; /**stored parsed argumnets **/
	size_t w = 20, bitm = 0; /** initial buffer size **/
	ssize_t numb_char; /** stores num of character **/

	while (1)
	{
		printf("cimba$ "); /** just testing **/
		ptr = malloc(sizeof(char) * w); /** dynamically allocate memory
						  * to input strin **/
		numb_char = getline(&ptr, &w, stdin); /**read user input and stroe in ptr **/
		if (numb_char == -1) /** check for errors **/
		{
			free(ptr);
			exit(EXIT_FAILURE);
		}

		if (*ptr != '\n') /** check for fork errors **/
		{
			strng = prstrtok(ptr);
			bitm = builtincheck(strng[0]);
			if (bitm == 0)
				exefork(strng);
			else if (bitm == 2)
				continue;
		}
	}
	free(ptr);
	free(strng);
	exit(0);
}
