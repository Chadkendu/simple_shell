#include "p_shell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

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
	pid_t child_pid; /** process ID **/
	char *ptr; /**stores input string **/
	char **strng; /**stored parsed argumnets **/
	int stats; /** stores child process status **/
	size_t w = 20; /** initial buffer size **/
	ssize_t numb_char; /** stores num of character **/

	while (1)
	{
		if (isatty(STDIN_FILENO)) /** check if stdin is a terminal device **/
			printf("cimba$ ");
		ptr = malloc(sizeof(char) * w); /** dynamically allocate memory
						  * to input strin **/
		numb_char = getline(&ptr, &w, stdin); /**read user input and stroe in ptr **/
		if (numb_char == -1) /** check for errors **/
		{
			free(ptr);
			exit(EXIT_FAILURE);
		}
		strng = prstrtok(ptr); /** parse input string into sepere ardument**/
		child_pid = fork(); /** creates a child process **/
		if (child_pid == -1) /** check for fork errors **/
		{
			perror("Fork issue");
			return (1);
		}
		if (child_pid == 0) /** execute command in child process **/
		{
			if (execvp(strng[0], strng) == -1)
				printf("[file or directory not found]\n");
		}
		else /** parent process **/
			wait(&stats); /** wait for child process to end **/
	}
	exit(0);
}
