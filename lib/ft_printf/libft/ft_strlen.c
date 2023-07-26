/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:26:30 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 13:30:43 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		i++;
	}
	return (i);
}

/*

ft_strlen:

PARAMETERS
-/-

RETURN VALUE
The strlen() function returns the number of characters that precede the 
terminating NUL character.


DESCRIPTION
The strlen() function computes the length of the string s. 
The strnlen() function attempts to compute the length of s, but never scans 
beyond the first maxlen bytes of s.

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