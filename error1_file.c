#include "nickdun.h" 

/** 

* _putsfd - prints input datatype str 

* @str: str that has to be printed. 

* @fd: filedescriptor that should be written on 

* 

* Return: The numbers characters printed 

*/ 

int _putsfd(char *str, int fd) 

{ 

	int i = 0; 

  

	if (!str) 

		return (0); 

	while (*str) 

	{ 

		i += _putfd(*str++, fd); 

	} 

	return (i); 

} 

/** 

* _eputchar - writes char c to standard error 

* @c: char to write 

* 

* Return: 1 if the condtion is success  

* if error, -1 , error number set correctly. 

*/ 

int _eputchar(char c) 

{ 

	static int r; 

	static char buf[WRITE_BUF_SIZE]; 

  

	if (c == BUF_FLUSH || r >= WRITE_BUF_SIZE) 

	{ 

		write(2, buf, r); 

		r= 0; 

	} 

	if (c != BUF_FLUSH) 

		buf[r++] = c; 

	return (1); 

} 

 

/** 

* _eputs - prints str 

* @str: str to be printed 

* 

* return: 0 

*/ 

void _eputs(char *str) 

{ 

	int r = 0; 

  

	if (!str) 

		return; 

	while (str[r] != '\0') 

	{ 

		_eputchar(str[r]); 

		r++; 

	} 

} 

  

  

/** 

* _putfd – write char c to file decriptor 

* @c: datatype char printed 

* @fd: to write filedescriptor  

* 

* Return:  1 if condition success 

* if error, -1  

*/ 

int _putfd(char c, int fd) 

{ 

	static int i; 

	static char buf[WRITE_BUF_SIZE]; 

  

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) 

	{ 

		write(fd, buf, i); 

		i = 0; 

	} 

	if (c != BUF_FLUSH) 

		buf[i++] = c; 

	return (1); 

}  
