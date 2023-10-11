/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_ll_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:17:58 by musenov           #+#    #+#             */
/*   Updated: 2023/10/11 18:21:41 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp_linked_list(t_minishell *shell)
{
	t_envp_ll	*head;
	char		**env;
	char		*var;
	char		*value;

	head = NULL;
	env = environ;
	while (*env)
	{
		parse_env_string(*env, &var, &value);
		add_to_list(&head, var, value);
		free(var);
		free(value);
		env++;
	}
	shell->envp_ll = head;
}

/*
	*equal_pos = '\0'; // Temporarily terminate the string at the equals sign
	*equal_pos = '='; // Restore the equals sign
*/

void	parse_env_string(char *str, char **var, char **value)
{
	char	*equal_pos;

	equal_pos = ft_strchr(str, '=');
	*equal_pos = '\0';
	*var = ft_strdup(str);
	*value = ft_strdup(equal_pos + 1);
	*equal_pos = '=';
}

void	add_to_list(t_envp_ll **head, char *var, char *value)
{
	t_envp_ll	*new_node;
	t_envp_ll	*temp;

	new_node = create_new_node(var, value);
	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_envp_ll	*create_new_node(char *var, char *value)
{
	t_envp_ll	*new_node;

	new_node = malloc(sizeof(t_envp_ll));
	if (!new_node)
		return (NULL);
	new_node->var = ft_strdup(var);
	new_node->value = ft_strdup(value);
	new_node->env_var = true;
	new_node->next = NULL;
	return (new_node);
}
