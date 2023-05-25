#ifndef _SHELL_H_
#define _SHELL_H_

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

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define NORM_CMD	0
#define OR_CMD		1
#define AND_CMD		2
#define CHAIN_CMD	3


#define CONVERT_LOWER	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE	".simple_shell_history"
#define HISTORY_MAX	4096

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
 *struct passinfo - contains pseudo-arguements to pass into a function,
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
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_c;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_c *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_c *, char **);
int find_builtin(info_c *);
void locate_cmd(info_c *);
void fork_cmd(info_c *);

/* toem_parser.c */
int is_cmd(info_c *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_c *, char *, char *);

/* hsh.c */
int hsh(char **);

/* toem_errors.c */
void _e_puts(char *);
int _e_put_char(char);
int _put_fd(char c, int fd);
int _puts_fd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_str_n_cpy(char *, char *, int);
char *_str_n_cat(char *, char *, int);
char *_str_chr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int is_interactive(info_c *);
int is_delimiter(char, char *);
int _is_alpha(int);
int a_to_i(char *);

/* toem_errors1.c */
int _err_atoi(char *);
void print_err(info_c *, char *);
int print_d(int, int);
char *convert_num(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int my_exit(info_c *);
int my_cd(info_c *);
int _myhelp(info_c *);

/* toem_builtin1.c */
int _my_history(info_c *);
int _my_alias(info_c *);

/*toem_getline.c */
ssize_t get_input(info_c *);
int _getline(info_c *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_c *);
void _set_info(info_c *, char **);
void _free_info(info_c *, int);

/* toem_environ.c */
char *_get_env(info_c *, const char *);
int _myenv(info_c *);
int my_set_env(info_c *);
int my_unset_env(info_c *);
int populate_env_list(info_c *);

/* toem_getenv.c */
char **get_envir(info_c *);
int _unset_env(info_c *, char *);
int _setenv(info_c *, char *, char *);

/* toem_history.c */
char *get_history_file(info_c *info);
int write_history(info_c *info);
int read_history(info_c *info);
int build_history_list(info_c *info, char *buf, int linecount);
int renumber_history(info_c *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_c *, char *, size_t *);
void check_chain(info_c *, char *, size_t *, size_t, size_t);
int replace_alias(info_c *);
int replace_vars(info_c *);
int replace_string(char **, char *);

#endif
