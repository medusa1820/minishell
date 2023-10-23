/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:20:24 by musenov           #+#    #+#             */
/*   Updated: 2023/10/22 13:43:38 by musenov          ###   ########.fr       */
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
		print_error_bltn(cmd[0], cmd[1], \
			"Arguments and options are not supported");
		return (EXIT_SUCCESS);
	}
	// return (print_error_bltn(*cmd, *(cmd + 1), "Arguments and options are not supported"), 0);
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

/* meder

int	env_bltn(char **envp_local, char **cmd)
{
	int	i;

	if (cmd[1])
	{
		print_error_bltn(cmd[0], cmd[1], "enter cmd w/o options/arguments");
		return (EXIT_SUCCESS);
	}
	i = 0;
	if (!envp_local)
		return (EXIT_FAILURE);
	while (envp_local[i])
		ft_putendl_fd(envp_local[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

*/



/* env_builtin:
*	Executes the builtin env command: Prints the environment variables.
*/

/* mccombeaou

int	env_builtin(t_data *data, char **args)
{
	int	i;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
		ft_putendl_fd(data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

*/

