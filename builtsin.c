#include "shell.h" 

/** 

* my_exitcode- exits shell 

* @descrb: Struct containing   arg that maintains 

* constant funct prototype. 

* Return: exits with specific status 

* (0) if data.argv[0] != "exit" 

*/ 

int my_exitcode(data_t *data) 

{ 

int exitcheck; 

  

if (data->argv[1]) /* If  exit arg */ 

{ 

exitcheck = _erratoi(data->argv[1]); 

if (exitcheck == -1) 

{ 

data->status = 2; 

fprint_error(data, " unknown number: "); 

_fputs(data->argv[1]); 

_fputchar('\n'); 

return (1); 

} 

data->err_num = _erratoi(data->argv[1]); 

return (-2); 

} 

data->err_num = -1; 

return (-2); 

} 

  

/** 

* my_cdcode – change the current directory 

*  @descrb: Struct containing   arg that maintains 

* Constant funct prototype. 

* Return:  0 Success 

*/ 

int my_cdcode(data_t *data) 

{ 

char *s, *dir, buffer[1024]; 

int chdir_ret; 

  

s = getcwd(buffer, 1024); 

if (!s) 

_puts("TODO: >>getcwd fails error here<<\n"); 

if (!data->argv[1]) 

{ 

dir = get_env(data, "HOME="); 

if (!dir) 

chdir_ret = /* TODO: whats next process? */ 

chdir((dir = get_env(data, "PWD=")) ? dir : "/"); 

else 

chdir_ret = chdir(dir); 

} 

else if (str_cmp(data->argv[1], "-") == 0) 

{ 

if (!get_env(data, "OLDPWD=")) 

{ 

_puts(s); 

_putchar('\n'); 

return (1); 

} 

_puts(get_env(data, "OLDPWD=")), _putchar('\n'); 

chdir_ret = /* TODO: what next process? */ 

chdir((dir = get_env(data, "OLDPWD=")) ? dir : "/"); 

} 

else 

chdir_ret = chdir(data->argv[1]); 

if (chdir_ret == -1) 

{ 

fprint_error(data, "can not cd to "); 

_fputs(data->argv[1]), _fputchar('\n'); 

} 

else 

{ 

set_env(data, "OLDPWD", get_env(data, "PWD=")); 

set_env(data, "PWD", getcwd(buffer, 1024)); 

} 

return (0); 

} 

  

/** 

* my_helpcode – change current directory 

* @descrb: Struct containing  arg that maintains 

* constant funct prototype 

* Return:  0 Success 

*/ 

int my_helpcode(data_t *data) 

{ 

char **arg_array; 

  

arg_array = data->argv; 

_puts("help call works well. Funct  yet to be implemented \n"); 

if (0) 

_puts(*arg_array); /* temporary att_unused workwithin */ 

return (0); 

} 
