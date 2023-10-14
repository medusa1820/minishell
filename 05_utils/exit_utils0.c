/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:37:58 by musenov           #+#    #+#             */
/*   Updated: 2023/10/14 14:25:04 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(int exit_code, char *error_msg, t_pipe *data)
{
	perror(error_msg);
	free_all(data);
	free_envp_ll(data->shell_data->envp_ll);
	free_envp_local(data->shell_data->envp_local);
	// free_ast(&data->shell_data->ast_root);
	free_ast(data->shell_data->ast_root);
	exit(exit_code);
}

void	error_do_next_iter(int exit_code, char *error_msg, t_pipe *data)
{
	perror(error_msg);
	// perror(exit_code);
	(void)exit_code;
	// free_all(data);
	// free_ast(&data->shell_data->ast_root);
	data->exit_code = 1;
}

void	free_all(t_pipe *data)
{
	free_str(data);
	free_2d_str(data);
}

void	free_str(t_pipe *data)
{
	if (data->cmd_path != NULL)
		free(data->cmd_path);
	data->cmd_path = NULL;
}

void	free_2d_str(t_pipe *data)
{
	if (data->paths != NULL)
		free_2d_str_func(data->paths);
}

void	free_2d_str_func(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free(str);
	str = NULL;
}
