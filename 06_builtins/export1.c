/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:12:11 by musenov           #+#    #+#             */
/*   Updated: 2023/11/27 11:31:25 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_bltn(t_envp_ll *head, char **cmd, t_minishell *shell)
{
	int		i;
	int		return_value;

	return_value = 0;
	i = 1;
	if (!cmd[i])
	{
		export_no_args(head);
		return (return_value);
	}
	while (cmd[i])
	{
		if (valid_identifier(cmd[i]))
		{
			if (ft_strchr(cmd[i], '='))
				export_var(head, cmd[i]);
		}
		else
		{
			if (cmd[1][0] == '-')
			{
				print_error_bltn("export", cmd[i], "options are not required");
				return_value = 2;
			}
			else
			{
				print_error_bltn("export", cmd[i], "not a valid identifier");
				return_value = 1;
			}
		}
		i++;
	}
	free_envp_local(shell->envp_local);
	envp_ll_to_envp_local(shell);
	return (return_value);
}
