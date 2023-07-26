/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:46:34 by musenov           #+#    #+#             */
/*   Updated: 2023/07/10 20:39:25 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	total_size;

	if (size > 0 && (UINT_MAX / size) < count)
		return (NULL);
	total_size = count * size;
	str = malloc(total_size);
	if (!str)
		return (NULL);
	ft_bzero(str, total_size);
	return (str);
}

/*

ft_calloc:

PARAMETERS
-/-

RETURN VALUE
If successful, calloc(), malloc(), realloc(), reallocf(), valloc(), and 
aligned_alloc() functions return a pointer to allocated memory. If there is 
an error, they return a NULL pointer and set errno to ENOMEM.

DESCRIPTION
The calloc() function contiguously allocates enough space for count
objects that are size bytes of memory each and returns a pointer to the
allocated memory.  The allocated memory is filled with bytes of value
zero.


QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
-/-

EXPLANATION
-/-

REMARK
test case from pain tester: overflow by one byte

UINT64_MAX - (274177 * 67280421310721) = -1

*/