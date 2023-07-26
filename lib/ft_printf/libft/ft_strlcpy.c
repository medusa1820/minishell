/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:10:59 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 01:11:18 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t	i;

	i = 0;
	if (dst_size > 0)
	{
		while (*(src + i) != '\0' && i < (dst_size - 1))
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
	while (*(src + i) != '\0')
		i++;
	return (i);
}

/*

ft_strlcpy:

PARAMETERS
-/-

RETURN VALUE
The strlcpy() and strlcat() functions return the total length of the 
string they tried to create. For strlcpy() that means the length of 
src.

If the return value is >= dstsize, the output string has been truncated. 
It is the caller's responsibility to handle this.



DESCRIPTION
strlcpy() and strlcat() take the full size of the destination buffer and 
guarantee NUL-termination if there is room.  Note that room for the NULL 
should be included in dstsize.

strlcpy() copies up to dstsize - 1 characters from the string src to dst, 
NUL-terminating the result if dstsize is not 0.

If the src and dst strings overlap, the behavior is undefined.

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
-/-


*/