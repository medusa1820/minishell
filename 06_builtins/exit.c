/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:51:09 by musenov           #+#    #+#             */
/*   Updated: 2023/10/14 14:29:23 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_on_exit(t_minishell *shell)
{
	// if (ms_data->p_input)
	// 	free(ms_data->p_input);
	// if (ms_data->var_head)
	// 	free_var_list(ms_data->var_head);
	// free_ast(&ms_data->parser_data);
	free_all(shell->data);
	free_envp_ll(shell->envp_ll);
	free_envp_local(shell->envp_local);
	// free_ast(&shell->ast_root);
	free_ast(shell->ast_root);
	rl_clear_history();
}

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
			error_printer("exit", cmd[1], "numeric argument required");
			exit_local = 255;
		}
	}
	if (arg_count > 2 && exit_local != 255)
	{
		error_printer("exit", NULL, "too many arguments");
		return (1);
	}
	if (exit_local < 0 || exit_local > 255)
		exit_local = exit_local % 256;
	free_on_exit(shell);
	// g_exit_code = exit_local;
	exit (exit_local);
}
