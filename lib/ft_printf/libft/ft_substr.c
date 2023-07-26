/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:23:10 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 16:13:00 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub_s = (char *)malloc(sizeof(*s) * (len + 1));
	if (!sub_s)
		return (0);
	i = 0;
	while (i < len)
	{
		*(sub_s + i++) = *(s + start++);
	}
	*(sub_s + i) = '\0';
	return (sub_s);
}

/*

ft_substr:

PARAMETERS
s: The string from which to create the substring. 
start: The start index of the substring in the string ’s’.
len: The maximum length of the substring.

RETURN VALUE
The substring.
NULL if the allocation fails.

DESCRIPTION
Allocates (with malloc(3)) and returns a substring from the string ’s’.
The substring begins at index ’start’ and is of maximum size ’len’.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
-/-

EXPLANATION

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	if (!s)
		return (0);
	if (start > ft_strlen(s))

below " ft_strdup("") " will return char pointer with '\0' at position 0

		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub_s = (char *)malloc(sizeof(*s) * (len + 1));
	if (!sub_s)
		return (0);
	i = 0;
	while (i < len)
	{
		*(sub_s + i++) = *(s + start++);
	}
	*(sub_s + i) = '\0';
	return (sub_s);
}

REMARK
-/-


*/
