/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:12:11 by musenov           #+#    #+#             */
/*   Updated: 2023/11/28 11:19:34 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_identifier(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

t_envp_ll	*find_var_node(t_envp_ll *head, char *cmd)
{
	t_envp_ll	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, cmd, ft_strlen(cmd) + 1) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	**make_var_value_pair(char *cmd)
{
	char	*equal_sign;
	char	**var_value_pair;

	equal_sign = ft_strchr(cmd, '=');
	var_value_pair = (char **)malloc(sizeof(char *) * 3);
	var_value_pair[0] = ft_substr(cmd, 0, equal_sign - cmd);
	var_value_pair[1] = ft_substr(equal_sign, 1, ft_strlen(equal_sign));
	var_value_pair[2] = NULL;
	return (var_value_pair);
}

int	export_var(t_envp_ll *head, char *cmd)
{
	t_envp_ll	*var_node;
	char		**var_value_pair;

	var_value_pair = make_var_value_pair(cmd);
	var_node = find_var_node(head, var_value_pair[0]);
	if (var_node)
	{
		return (export_var_if_var_node(var_node, var_value_pair));
	}
	else if (var_value_pair[1])
		add_to_list(&head, var_value_pair[0], var_value_pair[1]);
	else
		add_to_list(&head, var_value_pair[0], "");
	free_2d_str_func(var_value_pair);
	return (EXIT_SUCCESS);
}

int	export_var_if_var_node(t_envp_ll *var_node, char **var_value_pair)
{
	free(var_node->value);
	if (var_value_pair[1])
	{
		var_node->value = ft_strdup(var_value_pair[1]);
		if (!var_node->value)
		{
			free_2d_str_func(var_value_pair);
			return (EXIT_FAILURE);
		}
	}
	else
		var_node->value = ft_strdup("");
	var_node->env_var = true;
	free_2d_str_func(var_value_pair);
	return (EXIT_SUCCESS);
}
