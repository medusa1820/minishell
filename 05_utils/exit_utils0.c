/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:37:58 by musenov           #+#    #+#             */
/*   Updated: 2023/11/14 13:57:20 by musenov          ###   ########.fr       */
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
	// free_2d_str_cmd_split(data);
}

void	free_str(t_pipe *data)
{
	if (data->cmd_path != NULL)
	{
		free(data->cmd_path);
		data->cmd_path = NULL;
	}
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
		str[i] = NULL; // HEI YIU
		i++;
	}
	free(str);
	str = NULL;
}

/* void	free_2d_str_cmd_split(t_pipe *data)
{
	// printf("hiiiiiiiiiiiiii11111\n");
	if (data->cmd_split != NULL)
	// if (data->cmd_split)
	{
		// printf("hi before free\n");
		// printf("hi before free, %s\n", data->cmd_split[0]);
		free_2d_str_func(data->cmd_split);
		// printf("hi after free\n");
	}
} */

/* void	free_2d_str_cmd_split(t_pipe *data)
{
	if (data->cmd_split != NULL)
	{
		free_2d_str_func(data->cmd_split);
	}
} */


void free_2d_str_cmd_split(t_pipe *data)
{
	int		i;

	if (data == NULL || data->cmd_split == NULL)
	{
		printf("cmd_split is NULL\n");
		return ;
	}
	i = 0;
	while (data->cmd_split[i])
	{
		printf("%dth string: %s\n", i, data->cmd_split[i]);
		free(data->cmd_split[i]);
		data->cmd_split[i] = NULL;
		printf("freed and set to NULL\n");
		i++;
	}
	free(data->cmd_split);
	data->cmd_split = NULL;
	data->node->content->cmd = NULL;
	printf("pointer to array of strings freed and set to NULL\n");
}
