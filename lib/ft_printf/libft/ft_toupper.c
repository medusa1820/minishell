/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 01:55:12 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 01:12:06 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c = c - 32;
	return (c);
}

/*

ft_toupper:

PARAMETERS
-/-

RETURN VALUE
If the argument is a lower-case letter, the toupper() function returns the 
corresponding upper-case letter if there is one; otherwise, the argument is 
returned unchanged.

DESCRIPTION
The toupper() function converts a lower-case letter to the corresponding 
upper-case letter.  The argument must be representable as an unsigned char 
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
