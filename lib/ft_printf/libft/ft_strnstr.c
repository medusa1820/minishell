/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:37:53 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 15:12:10 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (0);
	i = 0;
	while (*(haystack + i) != '\0')
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j) && i + j < len)
		{
			if (*(haystack + i + j) == '\0' && *(needle + j) == '\0')
				return (((char *)haystack + i));
			j = j + 1;
		}
		if (*(needle + j) == '\0')
			return (((char *)haystack + i));
		i = i + 1;
	}
	return (0);
}

/*

ft_strnstr:

PARAMETERS
-/-

RETURN VALUE
- If needle is an empty string, haystack is returned;
- if needle occurs nowhere in haystack, NULL is returned;
- otherwise a pointer to the first character of the first occurrence of 
needle is returned.

DESCRIPTION
The strnstr() function locates the first occurrence of the null-terminated
string needle in the string haystack, where not more than len characters are
searched. Characters that appear after a '\0' character are 
not searched.

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
