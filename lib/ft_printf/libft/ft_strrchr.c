/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 00:08:36 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 13:42:43 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if ((char)c == *(s + i))
			return ((char *)s + i);
		i--;
	}
	return (0);
}

/*

ft_strrchr:

PARAMETERS
-/-

RETURN VALUE
The functions strchr() and strrchr() return a pointer to the located 
character, or NULL if the character does not appear in the string.

DESCRIPTION
The strchr() function locates the first occurrence of c (converted to 
a char) in the string pointed to by s.  The terminating null character 
is considered to be part of the string; therefore if c is `\0', the 
functions locate the terminating `\0'.

The strrchr() function is identical to strchr(), except it locates the 
last occurrence of c.

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
