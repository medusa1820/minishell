/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:42:41 by musenov           #+#    #+#             */
/*   Updated: 2023/10/12 14:29:11 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_no_args(t_envp_ll *var_head)
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

static int	is_valid_identifier(char *cmd)
{
	int	i;

	i = 1;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		error_printer("export", cmd, "not a valid identifier");
		return (0);
	}
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			error_printer("export", cmd, "not a valid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	export_one(t_envp_ll *var_head, char *cmd)
{
	t_envp_ll	*node_found;

	node_found = get_var_list_node(var_head, cmd);
	if (node_found != NULL)
	{
		if (modify_var_list_node(node_found, cmd) != 0)
			return (1);
		node_found->env_var = true;
	}
	else if (add_to_var_list(var_head, cmd, 1) != 0)
		return (1);
	return (0);
}

int	export_bltn(t_envp_ll *var_head, char **cmd)
{
	int			arg_count;
	int			index;
	int			return_value;

	index = 1;
	return_value = 0;
	arg_count = get_arg_count(cmd);
	if (arg_count == 1)
	{
		export_no_args(var_head);
		return (return_value);
	}
	while (cmd && *(cmd + index))
	{
		if (is_valid_identifier(*(cmd + index)))
		{
			if (export_one(var_head, *(cmd + index)) != 0)
				return (1);
		}
		else
			return_value = 1;
		index++;
	}
	return (return_value);
}
