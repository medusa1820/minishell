/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:41:18 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 19:26:19 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_bltn(t_envp_ll *head, char **cmd, t_minishell *shell)
{
	int			i;
	int			return_value;
	t_envp_ll	*node_to_unset;

	return_value = 0;
	i = 1;
	if (!cmd[i])
		return (return_value);
	while (cmd[i])
	{
		if (valid_identifier_unset(cmd[i]))
		{
			node_to_unset = find_var_node(head, cmd[i]);
			if (node_to_unset)
				remove_node(head, node_to_unset);
		}
		else
		{
			print_error_bltn("unset", cmd[i], "not a valid identifier");
			return_value = 1;
		}
		i++;
	}
	free_envp_local(shell->envp_local);
	envp_ll_to_envp_local(shell);
	return (return_value);
}

/* void	remove_node(t_envp_ll *var_head, t_envp_ll *found_node)
{
	t_envp_ll	*previous_node;

	previous_node = get_previous(var_head, found_node);
	if (previous_node == NULL)
		var_head = var_head->next;
	else
		previous_node->next = found_node->next;
	free_single_var_node(found_node);
} */

void	remove_node(t_envp_ll *head, t_envp_ll *node_to_unset)
{
	t_envp_ll	*current;
	t_envp_ll	*previous;

	current = head;
	previous = NULL;
	while (current != node_to_unset)
	{
		previous = current;
		current = current->next;
	}
	if (previous == NULL)
		head = head->next;
	else
		previous->next = node_to_unset->next;
	free_node(node_to_unset);
}

void	free_node(t_envp_ll *node_to_unset)
{
	free(node_to_unset->var);
	free(node_to_unset->value);
	free(node_to_unset);
}

/*
t_envp_ll	*get_previous(t_envp_ll *head, t_envp_ll *node_to_unset)
{
	t_envp_ll	*current;
	t_envp_ll	*previous;

	current = head;
	previous = NULL;
	while (current != node_to_unset)
	{
		previous = current;
		current = current->next;
	}
	return (previous);
}
*/
