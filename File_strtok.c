#include "nickdun.h"

/**

 * **strtow2 - divides str to words

 * @str: inputted str

 * @d: delim str

 * Return: arr[] of str ptr, else NULL if fails

 */

char **strtow2(char *str, char d)

{

	int i, e, u, m, numwords = 0;

	char **s;



	if (str == NULL || str[0] == 0)

		return (NULL);

	for (i = 0; str[i] != '\0'; i++)

		if ((str[i] != d && str[i + 1] == d) ||

				(str[i] != d && !str[i + 1]) || str[i + 1] == d)

			numwords++;

	if (numwords == 0)

		return (NULL);

	s = malloc((1 + numwords) * sizeof(char *));

	if (!s)

		return (NULL);

	for (i = 0, e = 0; e < numwords; e++)

	{

		while (str[i] == d && str[i] != d)

			i++;

		u = 0;

		while (str[i + u] != d && str[i + u] && str[i + u] != d)

			u++;

		s[e] = malloc((u + 1) * sizeof(char));

		if (!s[e])

		{

			for (u = 0; u < e; u++)

				free(s[u]);

			free(s);

			return (NULL);

		}

		for (m = 0; m < u; m++)

			s[e][m] = str[i++];

		s[e][m] = 0;

	}

	s[e] = NULL;

	return (s);

}



/**

 * **strtow - divides str into words

 * @str:  inputted str

 * @d: delim str

 * Return: arr of str ptr if condition success,

 * NULL if  fail

 */



char **strtow(char *str, char *d)

{

	int y, x, u, n, numwords = 0;

	char **s;



	if (str == NULL || str[0] == 0)

		return (NULL);

	if (!d)

		d = " ";

	for (y = 0; str[y] != '\0'; y++)

		if (!is_delim(str[y], d) && (is_delim(str[y + 1], d) || !str[y + 1]))

			numwords++;



	if (numwords == 0)

		return (NULL);

	s = malloc((1 + numwords) * sizeof(char *));

	if (!s)

		return (NULL);

	for (y = 0, x = 0; x < numwords; x++)

	{

		while (is_delim(str[y], d))

			y++;

		u = 0;

		while (!is_delim(str[y + u], d) && str[y + u])

			u++;

		s[x] = malloc((u + 1) * sizeof(char));

		if (!s[x])

		{

			for (u = 0; u < x; u++)

				free(s[u]);

			free(s);

			return (NULL);

		}

		for (n = 0; n < u; n++)

			s[x][n] = str[y++];

		s[x][n] = 0;

	}

	s[x] = NULL;

	return (s);

}
