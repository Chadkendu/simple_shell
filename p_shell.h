#ifndef P_SHELL_H
#define P_SHELL_H

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/** MACRO **/
#define MAX_ARGS 20

/** interactive mode **/
void parv(char **arv, char **envr);
/** prstrtok **/
char **prstrtok(char *strg);
/** p_getline function **/
ssize_t p_getline(char **lneptr, size_t *w, FILE *strm);

/** for builtincheck function **/
int builtincheck(char *strg);

/** exefork **/
void exefork(char **argument);

/** chkfile **/
int chkfile(char *strg);

/** p_strcmp **/
int p_strcmp(char *sr1, char *sr2);

/** command_exect **/
void command_exect(char *command, char *argv[], char **arv, char **envr);

/** check_command **/
int check_command(char *command, char **argument, char **environment);

/** p_strlent **/
int p_strlent(char *);

/** p_strcspn **/
size_t p_strcspn(const char *, char);

/** chkpath **/
int chkpath(char *str);

#endif
