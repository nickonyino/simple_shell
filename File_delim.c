#include "nickdun.h" 

/** 

* _atoi – changes str to integer 

* @x: the str to change 

* Return: if condition no numb in str 0, else change num 

*/ 

  

int _atoi(char *x) 

{ 

	int y, sign = 1, flag = 0, output; 

	unsigned int result = 0; 

  

	for (y = 0; x[y] != '\0' && flag != 2; y++) 

	{ 

		if (x[y] == '-') 

			sign *= -1; 

  

		if (x[y] >= '0' && x[y] <= '9') 

		{ 

			flag = 1; 

			result *= 10; 

			result += (x[y] - '0'); 

		} 

		else if (flag == 1) 

			flag = 2; 

	} 

  

	if (sign == -1) 

		output = -result; 

	else 

		output = result; 

  

	return (output); 

} 

 

/** 

* interactive – restore current shell in inter mod 

* @info: location strucure 

* 

* Return: if condition success 1 ,  0  if otherwise 

*/ 

int interactive(info_t *info) 

{ 

	return (isatty(STDIN_FILENO) && info->readfd <= 2); 

} 

  

/** 

* is_delim – look for delimeter characters 

* @c: to look for  character 

* @delim: string delim 

* Return: if condition true 1,  0 if condition is false 

*/ 

int is_delim(char c, char *delim) 

{ 

	while (*delim) 

		if (*delim++ == c) 

			return (1); 

	return (0); 

} 

  

/** 

* _isalpha – look  char which are aphabetic 

* @c: inserted  char 

* Return: if output alphabetic 1, 0 if not 

*/ 

  

int _isalpha(int c) 

{ 

	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 

		return (1); 

	else 

		return (0); 

} 
