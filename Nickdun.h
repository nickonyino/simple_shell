#ifndef NICKDUN_H 

#define NICKDUN_H 

 #include <string.h> 

#include <sys/types.h> 

 

size_t list_len(const list_t *); 

char **list_to_strings(list_t *); 

size_t print_list(const list_t *); 

list_t *node_starts_with(list_t *, char *, char); 

ssize_t get_node_index(list_t *, list_t *); 

#include <errno.h> 

#include <sys/wait.h> 

#include <sys/stat.h> 

#include <stdio.h> 

#include <stdlib.h> 

 

int is_cmd(info_t *, char *); 

char *dup_chars(char *, int, int); 

char *find_path(info_t *, char *, char *); 

 

#define READ_BUF_SIZE 1024 

#define WRITE_BUF_SIZE 1024 

#define BUF_FLUSH -1 

 

#include <unistd.h> 

#include <limits.h> 

#include <fcntl.h> 
 
#define CMD_NORM	0 

#define CMD_OR		1 

#define CMD_AND		2 

#define CMD_CHAIN	3 

  

#define CONVERT_LOWERCASE	1 

#define CONVERT_UNSIGNED	2 

  

#define USE_GETLINE 0 

#define USE_STRTOK 0 

  

#define HIST_FILE	".simple_shell_history" 

#define HIST_MAX	4096 

  

extern char **environ; 

  

  

/** 

* struct liststr - linked listed single 

* @num:  fields numbers 

* @str: the str 

* @next: next node ptr 

*/ 

typedef struct liststr 

{ 

	int num; 

	char *str; 

	struct liststr *next; 

} list_t; 

  

* @env: linked listed for local copies of environment 

* @environ: toiler mode copy of environ from LL env 

* @history: node history  

* @alias: node alias 

* @env_changed: whether environ changed  

* @status: the restored status of the last executed cmd 

* @cmd_buf: location ptr to cmd_buf, when in chain str 

* @cmd_buf_type: COMMAND_type ||, &&, ; 

* @readfd:  file descriptor to read inputted data 

* @histcount: hist line numb counted 

*/ 

typedef struct passinfo 

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

  

	char **cmd_buf; /* ptr cmd ;  buff chain, mem manag't */ 

	int cmd_buf_type; /* COMMAND_type ||, &&, ; */ 

	int readfd; 

	int histcount; 

} info_t; 

  
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}
   

int hsh(info_t *, char **); 

int find_builtin(info_t *); 

void find_cmd(info_t *); 

void fork_cmd(info_t *);  

int loophsh(char **); 

  

void _eputs(char *); 

int _eputchar(char); 

int _putfd(char c, int fd); 

int _putsfd(char *str, int fd); 

  

int _strlen(char *); 

int _strcmp(char *, char *); 

char *starts_with(const char *, const char *); 

char *_strcat(char *, char *); 

  

char *_strcpy(char *, char *); 

char *_strdup(const char *); 

void _puts(char *); 

int _putchar(char); 

 

char *_strncpy(char *, char *, int); 

char *_strncat(char *, char *, int); 

char *_strchr(char *, char); 

char **strtow(char *, char *); 

char **strtow2(char *, char); 

 

char *_memset(char *, char, unsigned int); 

void ffree(char **); 

void *_realloc(void *, unsigned int, unsigned int); 

  

int bfree(void **); 

  

int interactive(info_t *); 

int is_delim(char, char *); 

int _isalpha(int); 

int _atoi(char *); 

 

int _erratoi(char *); 

void print_error(info_t *, char *); 

int print_d(int, int); 

char *convert_number(long int, int, int); 

void remove_comments(char *); 

  

int _myexit(info_t *); 

int _mycd(info_t *); 

int _myhelp(info_t *); 

  

int _myhistory(info_t *); 

int _myalias(info_t *); 

 /** 

* struct builtin - holds built-in str and other funct 

* @type: cmd flag built-in 

* @func: funct 

*/ 

typedef struct builtin 

{ 

	char *type; 

	int (*func)(info_t *); 

} builtin_table; 

 

ssize_t get_input(info_t *); 

int _getline(info_t *, char **, size_t *); 

void sigintHandler(int); 

 

void clear_info(info_t *); 

void set_info(info_t *, char **); 

void free_info(info_t *, int); 

 

char *get_history_file(info_t *info); 

int write_history(info_t *info); 

int read_history(info_t *info); 

int build_history_list(info_t *info, char *buf, int linecount); 

int renumber_history(info_t *info); 

  

char *_getenv(info_t *, const char *); 

int _myenv(info_t *); 

int _mysetenv(info_t *); 

int _myunsetenv(info_t *); 

int populate_env_list(info_t *); 

  

char **get_environ(info_t *); 

int _unsetenv(info_t *, char *); 

int _setenv(info_t *, char *, char *); 

  

list_t *add_node(list_t **, const char *, int); 

list_t *add_node_end(list_t **, const char *, int); 

size_t print_list_str(const list_t *); 

int delete_node_at_index(list_t **, unsigned int); 

void free_list(list_t **); 

   

int is_chain(info_t *, char *, size_t *); 

void check_chain(info_t *, char *, size_t *, size_t, size_t); 

int replace_alias(info_t *); 

int replace_vars(info_t *); 

int replace_string(char **, char *); 

/** 

* struct passinfo - holds pseudo-args to direct to funct, 

* permitting similar prototype for funct ptr structure 

* @arg: str created from getline having parameters 

* @argv: array of str created from args 

* @path: str direction for current cmd 

* @argc: args total count 

* @line_count: the fail counts 

* @err_num: failure code for exit(s) 

* @linecount_flag: whether on count line of input 

* @fname: file-name of program 

 

  

#endif 
