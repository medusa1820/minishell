/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:40:00 by musenov           #+#    #+#             */
/*   Updated: 2023/07/10 20:42:35 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	left_trim;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (*(s1 + i) != '\0' && ft_strchr(set, *(s1 + i)) != NULL)
		i++;
	left_trim = i;
	i = ft_strlen(s1 + i);
	while (i > 0 && ft_strchr(set, *(s1 + left_trim + i)) != NULL)
		i--;
	return (ft_substr((s1 + left_trim), 0, i + 1));
}

	// while (*(s1 + i) != '\0' && ft_strchr(set, *(s1 + i)) > 0)
	// while (i > 0 && ft_strchr(set, *(s1 + left_trim + i)) > 0)

/*

ft_strtrim:

PARAMETERS
s1: The string to be trimmed.
set: The reference set of characters to trim.

RETURN VALUE
The trimmed string.
NULL if the allocation fails.

DESCRIPTION
Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters 
specified in ’set’ removed from the beginning and the end of the string.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (0);
	while (*s1 && strchr(set, *s1))
		s1++;
	i = strlen(s1);
	while (i && strchr(set, *s1))
		i--;
	return (ft_substr(s1, 0, i + 1));
}

EXPLANATION

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	left_trim;

	if (!s1 || !set)
		return (0);
	i = 0;

// trim on left of resulting string
	while (*(s1 + i) != '\0' && ft_strchr(set, *(s1 + i)) > 0)
		i++;

// store location of fore-left character of resulting string
	left_trim = i;

// get the length of string which would remain adter trim on the left 
// of the given string
	i = ft_strlen(s1 + i);
	
// trim on right of resulting string
	while (i > 0 && ft_strchr(set, *(s1 + left_trim + i)) > 0)
		i--;

// 0: start index of the substring in the string ’(s1 + left_trim)’
// it starts not at s1[0], but at s1[left_trim]
// i + 1: length of the substring.
	return (ft_substr((s1 + left_trim), 0, i + 1));
}


REMARK
-/-


*/
