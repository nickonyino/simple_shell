#include "nickdun.h"

/**

 **_strncat – Responsible for concatenation of two str

 *@dest: beginning str

 *@src: followed by second str

 *@n: total range of bytes to completely utilize

 *Return: joined str

 */

char *_strncat(char *dest, char *src, int n)

{

	int f, e;

	char *s = dest;



	f= 0;

	e= 0;

	while (dest[f] != '\0')

		f++;

	while (src[e] != '\0' && e < n)

	{

		dest[f] = src[e];

		f++;

		e++;

	}

	if (e < n)

		dest[f] = '\0';

	return (s);

}





/**

 **_strncpy – Responsible for copying str file

 *@dest: final destination str to be copied to

 *@src: origin source str to do the copying

 *@n: range of character to copy to str

 *Return: joints str

 */

char *_strncpy(char *dest, char *src, int n)

{

	int i, e;

	char *s = dest;



	i = 0;

	while (src[i] != '\0' && i < n - 1)

	{

		dest[i] = src[i];

		i++;

	}

	if (i < n)

	{

		e = i;

		while (e < n)

		{

			dest[e] = '\0';

			e++;

		}

	}

	return (s);

}





/**

 **_strchr - find charact in str

 *@s: str to use

 *@c: charact to find

 *Return: (s) the pointer to memory location s

 */

char *_strchr(char *s, char c)

{

	do {

		if (*s == c)

			return (s);

	} while (*s++ != '\0');



	return (NULL);

}
