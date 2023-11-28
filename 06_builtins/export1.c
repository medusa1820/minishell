/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:12:11 by musenov           #+#    #+#             */
/*   Updated: 2023/11/28 11:39:15 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_no_args(t_envp_ll *var_head)
{
	t_envp_ll	*current;

	current = var_head;
	while (current != NULL)
	{
		if (current->env_var == true)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(current->var, STDOUT_FILENO);
			if (current->value != NULL)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(current->value, STDOUT_FILENO);
				ft_putchar_fd('\"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		current = current->next;
	}
	return ;
}

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
			export_bltn_if_not_valid_identifier(cmd[1][0], cmd[i], \
												&return_value);
		i++;
	}
	free_envp_local(shell->envp_local);
	envp_ll_to_envp_local(shell);
	return (return_value);
}

void	export_bltn_if_not_valid_identifier(char c, char *str, \
											int *return_value)
{
	if (c == '-')
	{
		print_error_bltn("export", str, "options are not required");
		*return_value = 2;
	}
	else
	{
		print_error_bltn("export", str, "not a valid identifier");
		*return_value = 1;
	}
}
