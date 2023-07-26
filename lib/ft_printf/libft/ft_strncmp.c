/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 00:23:03 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 13:37:46 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (*(s1 + i) == *(s2 + i) && *(s1 + i) != '\0')
	{
		if (i < n - 1)
			i++;
		else
			return (0);
	}
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}

/*

ft_strncmp:

PARAMETERS
-/-

RETURN VALUE
The strcmp() and strncmp() functions return an integer greater than, 
equal to, or less than 0, according as the string s1 is greater than, 
equal to, or less than the string s2.  The comparison is done using 
unsigned characters, so that `\200' is greater than `\0'.


DESCRIPTION
The strcmp() and strncmp() functions lexicographically compare the 
null-terminated strings s1 and s2.

The strncmp() function compares not more than n characters.
Because strncmp() is designed for comparing strings rather than binary 
data, characters that appear after a `\0' character are not compared.

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