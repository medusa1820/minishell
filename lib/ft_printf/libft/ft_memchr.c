/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:01:12 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 00:36:50 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}

/*

ft_memchr:

PARAMETERS
-/-

RETURN VALUE
The memchr() function returns a pointer to the byte located, or NULL if 
no such byte exists within n bytes.

DESCRIPTION
The memchr() function locates the first occurrence of c (converted to an 
unsigned char) in string s.

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