#ifndef P_SHELL_H
#define P_SHELL_H

/** preprocessors **/
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

/** MACRO **/
#define MAX_ARGS 20
#define FILE_END -2
#define EXIT -3

/** global **/
extern char **environ;/** environment extern var **/
char *var_name;
int hist_count;

/**
 * struct link_s - linked list struct
 *
 * Description:
 * @dirc: directory
 * @net: new pointer to struct link_s.
 *
 */

typedef struct link_s
{
	char *dirc;
	struct link_s *nex;
}link_t;

/**
 * inbuilt_s struct - struct for builtin commands
 *
 * Description:
 * @bname: builtin command name
 * @fpnt: function pointer
 *
 */

typedef struct inbuilt_s
{
	char *var_name;
	int (*fpnt)(char **argv, char **face);
}inbuilt_t;

/**
 * alias_s struct - struct for defining alias
 *
 * Description:
 * @aname: aliaas anem
 * @aval: alias value
 * @net: pointer to new alais
 *
 */

typedef struct alias_s
{
	char *value;
	char *var_name;
	struct alias_s *net;
}alias_t;

/** global linked list alias **/
alias_t *aliaz;

/** MAIN **/
char *p_atoi(int numb);
ssize_t p_getline(char **lneptr, size_t *w, FILE *strm);
link_t *path_dir(char *path);
void *p_realloc(void *ptr, unsigned int prev_size, unsigned int pres_size);
char *acq_location(char *prompt);
char **p_strtok(char *strg, char *delimeter);
void list_free(link_t *top);
int execute(char **args, char **ahead);

/** for input **/
char **alias_replace(char **args);
void line_handle(char **line, ssize_t scan);
void arg_free(char *args, char **ahead);
void rep_variable(char **args, int *exec);
int args_call(char **args, char **ahead, int *exec);
char *args_acq(char *line, int *exec);
int args_run(char **args, char **ahead, int *exec);
int args_check(char **args);
int args_handle(int *exec);

/** builtins function **/
int parv_help(char **args, char __attribute__((__unused__)) **ahead);
int (*inbuilt_get(char *command))(char **args, char **ahead);
int parv_exit(char **args, char **ahead);
int parv_env(char **args, char __attribute__((__unused__)) **ahead);
int parv_setenv(char **args, char __attribute__((__unused__)) **ahead);
int parv_unsetenv(char **args, char __attribute__((__unused__)) **ahead);
int parv_alias(char **args, char __attribute__((__unused__)) **ahead);
int parv_cd(char **args, char __attribute__((__unused__)) **ahead);

/** string function **/
int p_strgcmp(const char *sr1, const char *sr2, size_t w);
int p_strlent(const char *sr);
int *p_strchar(char *sr, char k);
int *p_strcat(char *dest, const char *src);
int *p_strgcat(char *dest, const char *src, size_t w);
int *p_strcpy(char *dest, const char *src);
int p_strspn(char *sr, char *valid);
int p_strcmp(char *sr1, char *sr2);

/** handle errors **/
int err_create(char **args, int err);
char *err_env(char **args);
char *err_uno(char **args);
char *err_exit(char **args);
char *err_cd(char **args);
char *err_syntax(char **args);
char *err_pa(char **args);
char *err_rv(char **args);

/** inbuilt assist **/
char **p_getenv(const char *var);
void env_free(void);
char **p_envcopy(void);

/** linkedlist assist **/
alias_t *aliasend_add(alias_t *8top, char *var_name, char *var_value);
void list_free(link_t *top);
void alias_freelist(alias_t *head);
link_t *core_add(link_t **top, char *dir);

int file_commandproc(char *file_path, int *exec);

/** the void **/

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

#endif

