/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:00:47 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 00:37:40 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	if (fd < 0)
		return ;
	i = 0;
	while (*(s + i) != '\0')
	{
		ft_putchar_fd(*(s + i), fd);
		i++;
	}
}

/*

ft_putstr_fd:

PARAMETERS
s: The string to output.
fd: The file descriptor on which to write.

RETURN VALUE
None

DESCRIPTION
Outputs the string ’s’ to the given file descriptor.

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

REMARK
-/-


*/