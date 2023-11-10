/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:56:48 by musenov           #+#    #+#             */
/*   Updated: 2023/10/24 12:16:52 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////////////////////////// cd //////////////////////////////

char	*get_envp_ll_var_value(t_envp_ll *head, char *var)
{
	t_envp_ll	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strncmp(temp->var, var, ft_strlen(var) + 1) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	update_envp_ll_var_value(t_envp_ll *head, char *var, char *value)
{
	t_envp_ll	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strncmp(temp->var, var, ft_strlen(var) + 1) == 0)
		{
			if (temp->value)
				free(temp->value);
			temp->value = ft_strdup(value);
			if (temp->value == NULL)
				return (EXIT_FAILURE);
			break ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

////////////////////////////// echo //////////////////////////////