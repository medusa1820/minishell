/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:41:18 by musenov           #+#    #+#             */
/*   Updated: 2023/11/06 20:57:23 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	unset_is_valid_identifier(char *cmd)
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
} */

/* t_envp_ll	*get_previous(t_envp_ll *var_head, t_envp_ll *found_node)
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
} */

/* void	free_single_var_node(t_envp_ll *node)
{
	if (node->var)
		free(node->var);
	if (node->value)
		free(node->value);
	free(node);
} */

/* void	remove_found_node(t_envp_ll *var_head, t_envp_ll *found_node)
{
	t_envp_ll	*previous_node;

	previous_node = get_previous(var_head, found_node);
	if (previous_node == NULL)
		var_head = var_head->next;
	else
		previous_node->next = found_node->next;
	free_single_var_node(found_node);
} */

/* int	unset_bltn(t_envp_ll *var_head, char **cmd)
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
} */

/* unset_builtin:
*	Removes the environment variables with the given keys
*	after checking if they are valid keys.
*	Does nothing if the key is not in the environment.
*	Returns 0 if all args were successfully unset, or 1 if
*	one or more args could not be unset.
*/

/* int	unset_builtin(t_data *data, char **args)
{
	int	i;
	int	idx;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			errmsg_cmd("unset", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else
		{
			idx = get_env_var_index(data->env, args[i]);
			if (idx != -1)
				remove_env_var(data, idx);
		}
		i++;
	}
	return (ret);
} */

int	unset_bltn(t_envp_ll *head, char **cmd, t_minishell *shell)
{
	int			i;
	int			return_value;
	t_envp_ll	*node_to_unset;

	return_value = 0;
	i = 1;
	if (!cmd[i])
	{
		// export_no_args(head);
		return (return_value);
	}
	while (cmd[i])
	{
		if (valid_identifier(cmd[i]))
		{
			// if (ft_strchr(cmd[i], '='))
			// 	export_var(head, cmd[i]);
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
