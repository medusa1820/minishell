/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:51:09 by musenov           #+#    #+#             */
/*   Updated: 2023/11/27 11:23:13 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
