/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:01:07 by musenov           #+#    #+#             */
/*   Updated: 2023/10/10 15:03:04 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_sym(const char *s1, const char *s2, char c)
{
	char	*test_path;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	test_path = malloc(s1_len + s2_len + 2);
	if (!test_path)
		return (NULL);
	while (s1 && *s1 != 0)
		*test_path++ = *s1++;
	*test_path = c;
	test_path++;
	while (*s2 != '\0')
		*test_path++ = *s2++;
	*test_path = '\0';
	return (test_path - s1_len - s2_len - 1);
}

void	free_p(char	*p)
{
	if (p)
		free(p);
}

void	internal_error_printer(char *msg)
{
	ft_putstr_fd("minishell: internal error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}
