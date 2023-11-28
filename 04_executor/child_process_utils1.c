/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:21:08 by musenov           #+#    #+#             */
/*   Updated: 2023/11/28 18:41:01 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_cmd_not_found(t_pipe *data, int i)
{
	if (data->paths == NULL || data->paths[i] == NULL)
		exit_error_cmd_notfound(127, "Command not found: ", data);
}

void	close_pipe0_fds(t_pipe *data)
{
	close(data->pipe0_fd[0]);
	close(data->pipe0_fd[1]);
}

void	close_pipe1_fds(t_pipe *data)
{
	close(data->pipe1_fd[0]);
	close(data->pipe1_fd[1]);
}

bool	data_has_infile(t_pipe *data)
{
	return (data->fd_infile != STDIN_FILENO);
}

bool	data_has_outfile(t_pipe *data)
{
	return (data->fd_outfile != STDOUT_FILENO);
}
