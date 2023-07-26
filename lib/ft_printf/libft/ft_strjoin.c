/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:48:04 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 00:38:22 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i_s12;
	size_t	i_s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s3 == NULL)
		return (NULL);
	i_s3 = 0;
	i_s12 = 0;
	while (*(s1 + i_s12) != '\0')
	{
		*(s3 + i_s3++) = *(s1 + i_s12++);
	}
	i_s12 = 0;
	while (*(s2 + i_s12) != '\0')
	{
		*(s3 + i_s3++) = *(s2 + i_s12++);
	}
	*(s3 + i_s3) = '\0';
	return (s3);
}

/*

ft_strjoin:

PARAMETERS
s1: The prefix string.
s2: The suffix string.

RETURN VALUE
The new string.
NULL if the allocation fails.

DESCRIPTION
Allocates (with malloc(3)) and returns a new string, which is the result 
of the concatenation of ’s1’ and ’s2’.

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