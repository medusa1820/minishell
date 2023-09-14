/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:37:58 by musenov           #+#    #+#             */
/*   Updated: 2023/09/14 11:11:49 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(int exit_code, char *error_msg, t_pipe *data)
{
	perror(error_msg);
	free_all(data);
	exit(exit_code);
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
	// if (data->cmd_split != NULL)
	// 	free_2d_str_func(data->cmd_split);
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

void	exit_error_cmd_notfound(int exit_code, char *error_msg, t_pipe *data)
{
	printf("%s%s: %s\n", error_msg, data->cmd_split[0], strerror(errno));
	// free_ast_meder(data->shell_data->ast_root);
	// free_content(data->shell_data->ast_root->content);
	free_ast(&data->shell_data->ast_root);
	free_all(data);
	exit(exit_code);
}
