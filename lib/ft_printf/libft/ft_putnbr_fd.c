/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:07:27 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 00:37:27 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (fd < 0)
		return ;
	if (n >= 0)
		nb = n;
	else
		nb = -n;
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (nb < 10)
		ft_putchar_fd(nb + '0', fd);
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
}

/*

ft_putnbr_fd:

PARAMETERS
n: The integer to output.
fd: The file descriptor on which to write.

RETURN VALUE
None

DESCRIPTION
Outputs the integer ’n’ to the given file descriptor.

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