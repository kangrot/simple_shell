#ifndef _SIMSHELL_H
#define _SIMSHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define TOK_DEL " \n"
#define CMD_LEN 64
#define B_SIZE 1024

/* External access to environment variables */
extern char **environ;

/* Function for the main shell loop */
void simshell_loop(int argc, char **argv);

/* Function to read user input commands */
char *read_incom();

/* Function to tokenize input */
char **tok_input(char *linebuf);
char *simshell_strtok(char *string, const char *del);
void free_tok(char **tokens_made);

/* Function to execute commands */
int exec_com(char **tokens_made);

/* Function to check if a command exists in the system */
char *find_com(const char *cmd);

/* Simshell getenv function */
char *get_simshell_env(const char *variable_name);

/* Memory management function */
void *simshell_realloc(void *ptr, unsigned int old_s, size_t);

/* Built-in command controllers */
void control_b_com(char **tokens_made);
void exit_simshell(int status);
void simshell_env(void);

/* Error controlling function */
void control_err(const char *name, int cmd_count, const char *command);
