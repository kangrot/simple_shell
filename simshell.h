#ifndef _SIMSHELL_H
#define _SIMSHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define TOK_DELI " \n"
#define CMD_LENT 64
#define B_SIZE 1024

/* External access to environment variables */
extern char **environ;

/* Function for the main shell loop */
void simshell_loop(int argc, char **argv);

/* Function to read user input commands */
char *read_incom();

/* Function to tokenize input */
char **tok_input(char *linebuff);
char *simshell_strtok(char *string, const char *delim);
void free_tok(char **tokk_made);

/* Function to execute commands */
int exec_com(char **tokk_made);

/* Function to check if a command exists in the system */
char *find_com(const char *cmmd);

/* Simshell getenv function */
char *get_simshell_env(const char *variable_name);

/* Memory management function */
void *simshell_realloc(void *ptr, unsigned int old_si, size_t new_si);

/* Built-in command controllers */
void control_b_com(char **tokens_made);
void exit_simshell(int status);
void simshell_env(void);

/* Error controlling function */
void control_err(const char *namme, int cmmd_count, const char *cmmd,
const char *erromsg);
void output_str(int desc, const char *str);
void convert_str(int numm, char *str);

/* All String Function Implementations */
size_t strlen_sim(const char *s);
char *strcat_sim(char *dest, const char *src);
int strcmp_sim(char *s1, char *s2);
char *strchr_sim(const char *s, char c);
char *strdup_func(const char *s);
char *strncat_sim(char *dest, char *src, int n);
size_t strspn_sim(char *s, char *accept);
int strncmp_sim(const char *s1, const char *s2, int n);
char *strcpy_sim(char *dest, char *source);
char *strncpy_sim(char *dest, char *source, int n);
int atoi_sim(char *s);

int stat;

#endif
