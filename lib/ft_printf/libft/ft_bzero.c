/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:43:15 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 00:07:33 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *)s + i) = 0;
		i++;
	}
}

/*

ft_bzero:

PARAMETERS
-/-

RETURN VALUE
The memset() function returns its first argument.

DESCRIPTION
The bzero() function writes n zeroed bytes to the string s.  If n is zero,
bzero() does nothing.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
void ft_bzero(void *s, long unsigned int n)
{
	ft_memset(s, '\0', n);
}

EXPLANATION
-/-

REMARK
this line *((char *)s + i) = 0 can alternatively be written as follows
*(char*)(s + i) = 0;

*/