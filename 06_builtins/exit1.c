/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:51:09 by musenov           #+#    #+#             */
/*   Updated: 2023/11/27 18:47:50 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	white_space(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

bool	ft_atoi_ll_int(const char *str, long long int *result)
{
	unsigned long long	output;
	int					sign;
	int					i;

	sign = 1;
	i = 0;
	while (str[i] && white_space(str[i]))
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	output = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		output = output * 10 + (str[i] - '0');
		if (arg_out_of_range(sign, output))
			return (true);
		i++;
	}
	*result = output * sign;
	return (false);
}

/*

Checks if the number goes over LONG_MAX or LONG_MIN

*/

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
