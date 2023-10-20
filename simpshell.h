#ifndef _SIMPSHELL_H_
#define _SIMPSHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct simp_passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmmd_buff: address of pointer to cmd_buf, on if chaining
 *@cmmd_buff_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct simp_passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmmd_buff; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmmd_buff_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct simp_builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct simp_builtin
{
	char *type;
	int (*func)(info_t *);
} simp_builtin_table;


/* simpshloop.c */
int hsh(info_t *, char **);
int simp_find_builtin(info_t *);
void simp_find_cmmd(info_t *);
void simp_fork_cmmd(info_t *);

/* simparser.c */
int simp_is_cmd(info_t *, char *);
char *simp_dup_chars(char *, int, int);
char *simp_find_path(info_t *, char *, char *);

/* simploophsh.c */
int simp_loophsh(char **);

/* simperrors.c */
void simp_eputs(char *);
int simp_eputchar(char);
int simp_putfd(char, int);
int simp_putsfd(char *, int);

/* simpstri.c */
int simp_strlen(char *);
int simp_strcmp(char *, char *);
char *starts(const char *, const char *);
char *simp_strcat(char *, char *);

/* simpstri1.c */
char *simp_strcpy(char *, char *);
char *simp_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* simpexits.c */
char *simp_strncpy(char *, char *, int);
char *simp_strncat(char *, char *, int);
char *simp_strchr(char *, char);

/* simptok.c */
char **simp_strtow(char *, char *);
char **simp_strtow2(char *, char);

/* simprelloc.c */
char *simp_memset(char *, char, unsigned int);
void simp_ffree(char **);
void *simp_realloc(void *, unsigned int, unsigned int);

/* simp_memory.c */
int simp_bfree(void **);

/* simpatoi.c */
int simp_interactive(info_t *);
int simp_is_delim(char, char *);
int simp_isalpha(int);
int simp_atoi(char *);

/* simperr1.c */
int simp_erratoi(char *);
void printerror(info_t *, char *);
int printd(int, int);
char *conv_num(long int, int, int);
void rem_com(char *);

/* simpb.c */
int simp_myexit(info_t *);
int simp_mycd(info_t *);
int simp_myhelp(info_t *);

/* simpb1.c */
int simp_myhistory(info_t *);
int simp_myalias(info_t *);
int simp_unset_alias(info_t *, char *);
int simp_set_alias(info_t *, char *);
int simp_print_alias(list_t *);

/*simpgetline.c */
ssize_t simp_input_buf(info_t *info, char **, size_t *);
ssize_t simp_read_buf(info_t *info, char *, size_t *);
ssize_t simp_get_input(info_t *);
int simp_getline(info_t *, char **, size_t *);
void simp_sigintHandler(int);

/* simpgetinfo.c */
void simp_clear_info(info_t *);
void simp_set_info(info_t *, char **);
void simp_free_info(info_t *, int);

/* simpenvi.c */
int simp_myenv(info_t *);
char *simp_getenv(info_t *, const char *);
int simp_mysetenv(info_t *);
int simp_myunsetenv(info_t *);
int pop_env_list(info_t *);

/* simpgetenv.c */
char **get_environ(info_t *);
int simp_unsetenv(info_t *, char *);
int simp_setenv(info_t *, char *, char *);

/* simphist.c */
char *get_hist_file(info_t *);
int write_hist(info_t *);
int read_hist(info_t *);
int build_hist_list(info_t *, char *, int);
int renum_hist(info_t *);

/* simpl.c */
list_t *add_nod(list_t **, const char *, int);
list_t *add_nod_end(list_t **, const char *, int);
size_t print_list_stri(const list_t *);
int delete_nod_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* simpl1.c */
size_t list_leng(const list_t *);
char **list_to_stri(list_t *);
size_t print_list(const list_t *);
list_t *nod_starts(list_t *, char *, char);
ssize_t get_nod_index(list_t *, list_t *);

/* simpvars.c */
int simp_is_chain(info_t *, char *, size_t *);
void simp_check_chain(info_t *, char *,
		size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_vars(info_t *);
int rep_stri(char **, char *);

#endif
