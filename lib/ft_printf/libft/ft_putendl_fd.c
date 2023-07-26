/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:03:51 by musenov           #+#    #+#             */
/*   Updated: 2023/02/20 17:32:34 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
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
	ft_putchar_fd('\n', fd);
}

/*

ft_putendl_fd:

PARAMETERS
s: The string to output.
fd: The file descriptor on which to write.

RETURN VALUE
None

DESCRIPTION
Outputs the string ’s’ to the given file descriptor followed by a newline.

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