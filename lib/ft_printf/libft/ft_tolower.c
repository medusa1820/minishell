/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:54:03 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 01:12:01 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + 32;
	return (c);
}

/*

ft_tolower:

PARAMETERS
-/-

RETURN VALUE
If the argument is an upper-case letter, the tolower() function returns the 
corresponding lower-case letter if there is one; otherwise, the argument is 
returned unchanged.

DESCRIPTION
The tolower() function converts an upper-case letter to the corresponding 
lower-case letter.  The argument must be representable as an unsigned char 
or the value of EOF.

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
