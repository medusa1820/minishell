/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_ll_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:34:38 by musenov           #+#    #+#             */
/*   Updated: 2023/09/28 15:40:30 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp_ll(t_envp_ll *head)
{
	t_envp_ll	*current;

	current = head;
	while (current)
	{
		printf("Var: %s, Value: %s\n", current->var, current->value);
		current = current->next;
	}
}

void	free_envp_ll(t_envp_ll *head)
{
	t_envp_ll	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->var)
			free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
