/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:53:45 by musenov           #+#    #+#             */
/*   Updated: 2023/10/18 18:29:22 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_bltn(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	print_error_bltn("pwd", NULL, strerror(errno));
	free(cwd);
	return (EXIT_FAILURE);
}
