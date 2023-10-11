/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_calls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:37:13 by musenov           #+#    #+#             */
/*   Updated: 2023/10/11 18:36:53 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	return (false);
}

int	execute_bltn(t_minishell *shell, char **cmd)
{
	(void)shell;
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (echo_bltn(cmd));
	// if (ft_strncmp(cmd[0], "cd", 3) == 0)
	// 	return (builtin_cd(ms_data->var_head, cmd));
	// if (ft_strncmp(cmd[0], "env", 4) == 0)
	// 	return (builtin_env(ms_data->var_head, cmd));
	// if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	// 	return (builtin_pwd());
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (export_bltn(shell->envp_ll, cmd));
	// if (ft_strncmp(cmd[0], "unset", 6) == 0)
	// 	return (builtin_unset(ms_data, cmd));
	return (0);
}
