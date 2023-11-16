#include "nickdun.h" 

/** 

* ffree – release part of str 

* @pp: part of Str 

*/ 

void ffree(char **pp) 

{ 

	char **a = pp; 

  

	if (!pp) 

		return; 

	while (*pp) 

		free(*pp++); 

	free(a); 

} 

 

/** 

* _memset – load mem with const byte 

* @s: the Pointer to memory location 

* @b: the bytes to load*s with 

* @n: range of byte 

* Return: the pointer mem location s 

*/ 

char *_memset(char *s, char b, unsigned int n) 

{ 

	unsigned int y; 

  

	for (y = 0; y < n; y++) 

		s[y] = b; 

	return (s); 

} 

  

/** 

* _realloc – the realloc size of mem 

* @ptr: the pointer to former mem 

* @old_size: the Byte range 

* @new_size: the Byte of new mem range 

* 

* Return: the ptr mem size block 

*/ 

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size) 

{ 

	char *p; 

  

	if (!ptr) 

		return (malloc(new_size)); 

	if (!new_size) 

		return (free(ptr), NULL); 

	if (new_size == old_size) 

		return (ptr); 

  

	p = malloc(new_size); 

	if (!p) 

		return (NULL); 

  

	old_size = old_size < new_size ? old_size : new_size; 

	while (old_size--) 

		p[old_size] = ((char *)ptr)[old_size]; 

	free(ptr); 

	return (p); 

} 
