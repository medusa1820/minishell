/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:53:45 by musenov           #+#    #+#             */
/*   Updated: 2023/10/12 18:54:13 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_bltn(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	if (pwd == NULL)
	{
		error_printer("pwd", NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (EXIT_SUCCESS);
}
