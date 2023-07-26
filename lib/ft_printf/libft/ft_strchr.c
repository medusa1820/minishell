/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:00:24 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 13:45:20 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (*(s + i) == (char)c)
		return (((char *)s + i));
	return (0);
}

/*

ft_strchr:

PARAMETERS
-/-

RETURN VALUE
The functions strchr() and strrchr() return a pointer to the located 
character, or NULL if the character does not appear in the string.

DESCRIPTION
The strchr() function locates the first occurrence of c (converted to a 
char) in the string pointed to by s.  The terminating null character is 
considered to be part of the string; therefore if c is `\0', the functions 
locate the terminating `\0'.

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