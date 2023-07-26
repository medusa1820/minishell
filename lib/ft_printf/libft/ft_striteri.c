/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:54:27 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 16:07:48 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (*(s + i) != '\0')
	{
		f(i, (s + i));
		i++;
	}
}

/*

ft_striteri:

PARAMETERS
s: The string on which to iterate.
f: The function to apply to each character.

RETURN VALUE
None

DESCRIPTION
Applies the function ’f’ on each character of the string passed as 
argument, passing its index as first argument. Each character is 
passed by address to ’f’ to be modified if necessary.

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