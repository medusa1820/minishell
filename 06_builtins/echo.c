/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:46 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 19:16:32 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_print_strs(char **cmd, bool *n_option)
{
	int		i;

	if (*n_option)
		i = 2;
	else
		i = 1;
	while (cmd[i])
	{
		if (!check_n_option(cmd[i]))
			break ;
		i++;
	}
	if (cmd[i])
		ft_putstr_fd(cmd[i++], STDOUT_FILENO);
	while (cmd[i])
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(cmd[i++], STDOUT_FILENO);
	}
	if (*n_option)
		return ;
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
}

bool	check_n_option(char *cmd)
{
	if (!cmd || *cmd != '-')
		return (false);
	cmd++;
	while (cmd && *cmd == 'n')
		cmd++;
	if (*cmd == '\0')
		return (true);
	return (false);
}

int	echo_bltn(char **cmd)
{
	bool	n_option;

	n_option = check_n_option(cmd[1]);
	echo_print_strs(cmd, &n_option);
	return (EXIT_SUCCESS);
}
