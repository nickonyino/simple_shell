#include "Nickdun.h" 

 /** 

* print_error - printing fail messg 

* @info: args & output data structure 

* @estr: str holds specific error types 

* Return: 0 if condition success, -1 if error 

*/ 

void print_error(info_t *info, char *estr) 

{ 

	_eputs(info->fname); 

	_eputs(": "); 

	print_d(info->line_count, STDERR_FILENO); 

	_eputs(": "); 

	_eputs(info->argv[0]); 

	_eputs(": "); 

	_eputs(estr); 

} 

 

/** 

* _erratoi – turns str to integer 

* @s: str to turn. 

* Return: 0 if condition success, -1 if error 

*/ 

int _erratoi(char *s) 

{ 

	int i = 0; 

	unsigned long int result = 0; 

  

	if (*s == '+') 

		s++;  /* TODO: reason why main return 255? */ 

	for (i = 0;  s[i] != '\0'; i++) 

	{ 

		if (s[i] >= '0' && s[i] <= '9') 

		{ 

			result *= 10; 

			result += (s[i] - '0'); 

			if (result > INT_MAX) 

				return (-1); 

		} 

		else 

			return (-1); 

	} 

	return (result); 

} 

  

  

/** 

* print_d – the funct for printing  dec (int) number (to base 10) 

* @input: data input  

* @fd: the fd to print on 

* 

* Return: the range of printed character 

*/ 

int print_d(int input, int fd) 

{ 

	int (*__putchar)(char) = _putchar; 

	int i, counter = 0; 

	unsigned int _abs_, current; 

  

	if (fd == STDERR_FILENO) 

		__putchar = _eputchar; 

	if (input < 0) 

	{ 

		_abs_ = -input; 

		__putchar('-'); 

		counter++; 

	} 

	else 

		_abs_ = input; 

	current = _abs_; 

	for (i = 1000000000; i > 1; i /= 10) 

	{ 

		if (_abs_ / i) 

		{ 

			__putchar('0' + current / i); 

			counter++; 

		} 

		current %= i; 

	} 

	__putchar('0' + current); 

	counter++; 

  

	return (counter); 

} 

  

/** 

* convert_number - change funct, clone itoa 

* @num: range number 

* @base: base unit 

* @flags: parameter flags 

* 

* Return: str 

*/ 

char *convert_number(long int num, int base, int flags) 

{ 

	static char *array; 

	static char buffer[50]; 

	char sign = 0; 

	char *ptr; 

	unsigned long y = num; 

  

	if (!(flags & CONVERT_UNSIGNED) && num < 0) 

	{ 

		y = -num; 

		sign = '-'; 

  

	} 

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF"; 

	ptr = &buffer[49]; 

	*ptr = '\0'; 

  

	do	{ 

		*--ptr = array[y % base]; 

		y /= base; 

	} while (y != 0); 

  

	if (sign) 

		*--ptr = sign; 

	return (ptr); 

} 

  

/** 

* remove_comments – the funct changes first appearance of '#' with '\0' 

* @buf: str location that needs modification 

* 

* Return:  0 if condition Success; 

*/ 

void remove_comments(char *buf) 

{ 

	int f; 

  

	for (f = 0; buf[f] != '\0'; f++) 

		if (buf[f] == '#' && (!f || buf[f - 1] == ' ')) 

		{ 

			buf[f] = '\0'; 

			break; 

		} 

} 
