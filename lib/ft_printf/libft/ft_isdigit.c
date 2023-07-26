/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:34:23 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 00:14:19 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/*

ft_isdigit:

PARAMETERS
-/-

RETURN VALUE
The isdigit() and isnumber() functions return zero if the character 
tests false and return non-zero if the character tests true.

DESCRIPTION
The isdigit() function tests for a decimal digit character.  Regardless 
	of locale, this includes the following characters only:

	``0''         ``1''         ``2''         ``3''         ``4''
	``5''         ``6''         ``7''         ``8''         ``9''

	The value of the argument must be representable as an unsigned char or 
	the value of EOF.

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