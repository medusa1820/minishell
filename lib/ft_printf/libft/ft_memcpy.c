/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:23:46 by musenov           #+#    #+#             */
/*   Updated: 2022/12/08 18:27:15 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (n == 0 || dst == src)
		return (dst);
	i = 0;
	while (i < n)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dst);
}

/*

ft_memcpy:

PARAMETERS
-/-

RETURN VALUE
The memcpy() function returns the original value of dst.

DESCRIPTION
The memcpy() function copies n bytes from memory area src to memory area dst. 
If dst and src overlap, behavior is undefined. Applications in which dst 
and src might overlap should use memmove(3) instead.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
-/-

EXPLANATION

	0123456789ABC
	   |  |
	   d  s   n = 5    -> s: src, d: dst
	result:
	   6789A89ABC

	0123456789ABC
	   |  |
	   s  d   n = 5    -> s: src, d: dst
	result:
	      34534BC

REMARK
Memory overlap not possible, use memmove for that


*/