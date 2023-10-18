/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:41:18 by musenov           #+#    #+#             */
/*   Updated: 2023/10/18 18:26:45 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_is_valid_identifier(char *cmd)
{
	int	i;

	i = 1;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		print_error_bltn("unset", cmd, "not a valid identifier");
		return (0);
	}
	while (cmd[i] != '\0')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			print_error_bltn("unset", cmd, "not a valid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}

t_envp_ll	*get_previous(t_envp_ll *var_head, t_envp_ll *found_node)
{
	t_envp_ll	*current;
	t_envp_ll	*previous;

	previous = NULL;
	current = var_head;
	while (current != found_node)
	{
		previous = current;
		current = current->next;
	}
	return (previous);
}

void	free_single_var_node(t_envp_ll *node)
{
	if (node->var)
		free(node->var);
	if (node->value)
		free(node->value);
	free(node);
}

void	remove_found_node(t_envp_ll *var_head, t_envp_ll *found_node)
{
	t_envp_ll	*previous_node;

	previous_node = get_previous(var_head, found_node);
	if (previous_node == NULL)
		var_head = var_head->next;
	else
		previous_node->next = found_node->next;
	free_single_var_node(found_node);
}

int	unset_bltn(t_envp_ll *var_head, char **cmd)
{
	int			arg_count;
	int			index;
	int			return_value;
	t_envp_ll	*node_found;

	index = 1;
	return_value = 0;
	arg_count = get_arg_count(cmd);
	if (arg_count == 1)
		return (return_value);
	while (cmd && *(cmd + index))
	{
		if (unset_is_valid_identifier(*(cmd + index)))
		{
			node_found = get_var_list_node(var_head, *(cmd + index));
			if (node_found != NULL)
				remove_found_node(var_head, node_found);
		}
		else
			return_value = 1;
		index++;
	}
	return (return_value);
}
