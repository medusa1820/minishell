/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:51:09 by musenov           #+#    #+#             */
/*   Updated: 2023/11/27 18:47:44 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_bltn(t_minishell *shell, char **cmd)
{
	long long int	exit_code_local;
	int				nbr_args;

	nbr_args = count_nbr_args(cmd);
	if (nbr_args >= 2)
	{
		if (exit_bltn_nbr_args_goe_2(cmd[1]) == 255)
			exit_code_local = 255;
		else
			return (1);
	}
	else if (nbr_args == 1)
	{
		exit_bltn_nbr_args_e_1(cmd[1], &exit_code_local);
	}
	else
		exit_code_local = shell->data->exit_code;
	if (exit_code_local < 0 || exit_code_local > 255)
		exit_code_local = exit_code_local % 256;
	free_before_exit(shell);
	exit (exit_code_local);
}

int	exit_bltn_nbr_args_goe_2(char *str)
{
	if (has_non_numeric_args(str))
	{
		print_error_bltn("exit", str, ": enter numeric argument");
		return (255);
	}
	else
	{
		print_error_bltn("exit", NULL, ": enter no more than 1 argument");
		return (1);
	}
}

void	exit_bltn_nbr_args_e_1(char *str, long long int *exit_code_local)
{
	if (has_non_numeric_args(str) || \
		ft_atoi_ll_int(str, exit_code_local))
	{
		print_error_bltn("exit", str, ": enter numeric argument");
		*exit_code_local = 255;
	}
}

int	count_nbr_args(char **cmd)
{
	int		i;

	i = 0;
	while (cmd && cmd[i])
		i++;
	return (i - 1);
}

bool	has_non_numeric_args(char *cmd)
{
	int	i;

	i = 0;
	while (white_space(cmd[i]))
		i++;
	if (cmd[i] == '\0')
		return (true);
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	if (!ft_isdigit(cmd[i]))
		return (true);
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]) && !white_space(cmd[i]))
			return (true);
		i++;
	}
	return (false);
}
