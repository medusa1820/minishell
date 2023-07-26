/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:25:22 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 00:37:14 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*((unsigned char *)b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}

/*

ft_memset:

PARAMETERS
-/-

RETURN VALUE
The memset() function returns its first argument.

DESCRIPTION
The memset() function writes len bytes of value c (converted to an 
unsigned char) to the string b.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
this solution is more clear for me
*((unsigned char *)b + i) = (unsigned char)c; 

these 2 below also work the same as the one above
*(unsigned char *)(b + i) = (unsigned char)c;
((unsigned char *)b)[i] = c;

EXPLANATION
-/-

REMARK
-/-


*/