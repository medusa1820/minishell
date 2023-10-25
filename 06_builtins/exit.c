/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:51:09 by musenov           #+#    #+#             */
/*   Updated: 2023/10/25 22:06:27 by musenov          ###   ########.fr       */
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
		if (has_non_numeric_args(cmd[1]))
		{
			print_error_bltn("exit", cmd[1], ": enter numeric argument");
			exit_code_local = 255;
		}
		else
		{
			print_error_bltn("exit", NULL, ": enter no more than 1 argument");
			return (1);
		}
	}
	else if (nbr_args == 1)
	{
		if (has_non_numeric_args(cmd[1]) || \
			ft_atoi_ll_int(cmd[1], &exit_code_local))
		{
			print_error_bltn("exit", cmd[1], ": enter numeric argument");
			exit_code_local = 255;
		}
	}
	else
		exit_code_local = shell->data->exit_code;
	if (exit_code_local < 0 || exit_code_local > 255)
		exit_code_local = exit_code_local % 256;
	free_before_exit(shell);
	exit (exit_code_local);
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

bool	white_space(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (true);
	return (false);
}

bool	ft_atoi_ll_int(const char *str, long long int *result)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && white_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (arg_out_of_range(neg, num))
			return (true);
		i++;
	}
	*result = num * neg;
	return (false);
}

// Checks if the number goes over LONG_MAX or LONG_MIN
bool	arg_out_of_range(int neg, unsigned long long num)
{
	return ((neg == 1 && num > LONG_MAX) || \
			(neg == -1 && num > -(unsigned long)LONG_MIN));
}

void	free_before_exit(t_minishell *shell)
{
	free_all(shell->data);
	free_envp_ll(shell->envp_ll);
	free_envp_local(shell->envp_local);
	free_ast(shell->ast_root);
	rl_clear_history();
}

/*

int	exit_bltn(t_minishell *shell, char **cmd)
{
	long long int	exit_local;
	int				arg_count;

	arg_count = get_arg_count(cmd);
	if (arg_count == 1)
		exit_local = shell->data->exit_code;
	if (arg_count > 1)
	{
		if (cmd[1][0] == '\0' || ft_atoi_secure(cmd[1], &exit_local) != 0)
		{
			print_error_bltn("exit", cmd[1], ": enter numeric argument");
			exit_local = 255;
		}
	}
	if (arg_count > 2 && exit_local != 255)
	{
		print_error_bltn("exit", NULL, ": enter no more than 1 argument");
		return (1);
	}
	if (exit_local < 0 || exit_local > 255)
		exit_local = exit_local % 256;
	free_before_exit(shell);
	// g_exit_code = exit_local;
	exit (exit_local);
}

*/
