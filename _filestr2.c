#include "nickdun.h" 

/** 

* _puts - writes inputted str 

* @str: written str 

* 

* Return: NULL 

*/ 

void _puts(char *str) 

{ 

	int y= 0; 

  

	if (!str) 

		return; 

	while (str[y] != '\0') 

	{ 

		_putchar(str[y]); 

		y++; 

	} 

} 

/** 

* _strcpy - replicate str 

* @dest: end 

* @src:  origin 

* 

* Return: the end ptr 

*/ 

char *_strcpy(char *dest, char *src) 

{ 

	int y = 0; 

  

	if (dest == src || src == 0) 

		return (dest); 

	while (src[y]) 

	{ 

		dest[y] = src[y]; 

		y++; 

	} 

	dest[y] = 0; 

	return (dest); 

}  

  

/** 

* _putchar - compose character c stdout 

* @c:  compose char 

* 

* Return: 1 if condition success, 

* -1 if condition fails, and failnumber set correctly. 

*/ 

int _putchar(char c) 

{ 

	static int y; 

	static char buf[WRITE_BUF_SIZE]; 

  

	if (c == BUF_FLUSH || y >= WRITE_BUF_SIZE) 

	{ 

		write(1, buf, y); 

		y = 0; 

	} 

	if (c != BUF_FLUSH) 

		buf[y++] = c; 

	return (1); 

} 

/** 

* _strdup - copies str 

* @str: str for copying 

* 

* Return: copied str ptr 

*/ 

char *_strdup(const char *str) 

{ 

	int length = 0; 

	char *ret; 

  

	if (str == NULL) 

		return (NULL); 

	while (*str++) 

		length++; 

	ret = malloc(sizeof(char) * (length + 1)); 

	if (!ret) 

		return (NULL); 

	for (length++; length--;) 

		ret[length] = *--str; 

	return (ret); 

} 
