#include "Nickdun.h" 

/** 

* _strcat - joins two str 

* @dest: end buffer str 

* @src: original buffer 

* 

* Return: the Ptr if success 

*/ 

char *_strcat(char *dest, char *src) 

{ 

	char *ret = dest; 

  

	while (*dest) 

		dest++; 

	while (*src) 

		*dest++ = *src++; 

	*dest = *src; 

	return (ret); 

} 

 

/** 

* _strlen – restore str length 

* @s: to check str length 

* 

* Return: len of int str success  

*/ 

int _strlen(char *s) 

{ 

	int y = 0; 

  

	if (!s) 

		return (0); 

  

	while (*s++) 

		y++; 

	return (y); 

} 

  

/** 

* _strcmp – corelate two str 

* @s1: beginning str 

* @s2: next str 

* 

* Return:   if s1 > s2 positve, if s1 == s2 zero , if s1 < s2 negative 

*/ 

int _strcmp(char *s1, char *s2) 

{ 

	while (*s1 && *s2) 

	{ 

		if (*s1 != *s2) 

			return (*s1 - *s2); 

		s1++; 

		s2++; 

	} 

	if (*s1 == *s2) 

		return (0); 

	else 

		return (*s1 < *s2 ? -1 : 1); 

} 

  

/** 

* starts_with – looks whether needle begins with haystack 

* @haystack: str to look 

* @needle: the substr 

* 

* Return: location of followed character  or NULL 

*/ 

char *starts_with(const char *haystack, const char *needle) 

{ 

	while (*needle) 

		if (*needle++ != *haystack++) 

			return (NULL); 

	return ((char *)haystack); 

} 
