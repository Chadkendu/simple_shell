#ifndef P_SHELL_H
#define P_SHELL_H

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
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
void exefork(char **argument, char *envi[]);

/** chkfile **/
char *chkfile(char *strg);

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

/** strcat **/
char *p_strcat(char *dest, char *src);

/** generate_path **/
char *generate_path(char *command);

/** chk_cmdpath **/
int chk_cmdpath(char *command);

/** line_split **/
char **line_split(char *command);

/** exec_command **/
void exec_command(char **, char **, char **);


/** stringfunction **/
char *p_strcat(char *, char *);


/**
 * struct inbuilt_s - builtin command struct
 *
 * Description:
 * @command: executed builtin command
 * @f_ptr: function pointer
 *
 * Return: void
 */

typedef struct inbuilt_s
{
	char *command;
	size_t (*f_ptr)(char **);
}inbuilt_t;

/** p_atoi **/
int p_atoi(char *);

/** inbuilt function **/
size_t p_exit(char **);
size_t p_setenv(char **);

/** inbuilt_match **/
size_t inbuilt_match(char **);

#endif
