/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:10:19 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 13:35:08 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s)
		return (0);
	i = 0;
	str = (char *)malloc(sizeof(*s) * (ft_strlen(s)) + 1);
	if (!str)
		return (0);
	while (*(s + i) != '\0')
	{
		*(str + i) = f(i, *(s + i));
		i++;
	}
	*(str + i) = '\0';
	return (str);
}

/*

ft_strmapi:

PARAMETERS
s: The string on which to iterate.
f: The function to apply to each character.

RETURN VALUE
The string created from the successive applications of ’f’.
Returns NULL if the allocation fails.


DESCRIPTION
Applies the function ’f’ to each character of the string ’s’, and 
passing its index as first argument to create a new string 
(with malloc(3)) resulting from successive applications of ’f’.

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