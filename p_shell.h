#ifndef P_SHELL_H
#define P_SHELL_H

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/** interactive mode **/
void parv(char **arv, char **envr);
/** prstrtok **/
char **prstrtok(char *strg);

#endif
