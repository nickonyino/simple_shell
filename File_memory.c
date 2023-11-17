#include "nickdun.h"

/**

 * bfree – release pointer NULL location

 * @ptr: location of pointer to release

 *

 * Return: 1 if condition success,if else 0

 */

int bfree(void **ptr)

{

	if (ptr && *ptr)

	{

		free(*ptr);

		*ptr = NULL;

		return (1);

	}

	return (0);

}
