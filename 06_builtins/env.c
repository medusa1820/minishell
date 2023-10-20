/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:20:24 by musenov           #+#    #+#             */
/*   Updated: 2023/10/18 18:34:00 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_bltn(t_envp_ll *var_list, char **cmd)
{
	t_envp_ll	*current;
	int			arg_count;

	current = var_list;
	arg_count = get_arg_count(cmd);
	if (arg_count > 1)
	{
		print_error_bltn(*cmd, *(cmd + 1), \
			"Arguments and options are not supported");
		return (EXIT_SUCCESS);
	}
		// return (print_error_bltn(*cmd, *(cmd + 1), 
		// 	"Arguments and options are not supported"), 0);
	while (current != NULL)
	{
		if (current->env_var == 1)
		{
			if (current->var && current->value)
			{
				ft_putstr_fd(current->var, STDOUT_FILENO);
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putendl_fd(current->value, STDOUT_FILENO);
			}
		}
		current = current->next;
	}
	return (0);
}
