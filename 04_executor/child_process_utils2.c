/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:18:51 by musenov           #+#    #+#             */
/*   Updated: 2023/11/19 14:02:09 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_pipe_in_out(t_pipe *data)
{
	if (data_has_infile(data))
		dup2_fd_infile_std_in(data);
	if (data_has_outfile(data))
		dup2_fd_outfile_std_out(data);
	else
		dup2(data->pipe0_fd[1], STDOUT_FILENO); // 4, out
}

void	dup2_fd_infile_std_in(t_pipe *data)
{
	dup2(data->fd_infile, STDIN_FILENO);
	close(data->fd_infile);
}

void	dup2_fd_outfile_std_out(t_pipe *data)
{
	dup2(data->fd_outfile, STDOUT_FILENO);
	close(data->fd_outfile);
}

void	middle_pipe_in_out(t_pipe *data, int *i)
{
	if (*i % 2 == 0)
	{
		if (data_has_infile(data))
			dup2_fd_infile_std_in(data);
		else
			dup2(data->pipe1_fd[0], STDIN_FILENO); // 5, in
		if (data_has_outfile(data))
			dup2_fd_outfile_std_out(data);
		else
			dup2(data->pipe0_fd[1], STDOUT_FILENO); // 4, out
	}
	else
	{
		if (data_has_infile(data))
			dup2_fd_infile_std_in(data);
		else
			dup2(data->pipe0_fd[0], STDIN_FILENO); // 3, in
		if (data_has_outfile(data))
			dup2_fd_outfile_std_out(data);
		else
			dup2(data->pipe1_fd[1], STDOUT_FILENO); // 6, out
	}
}

void	last_pipe_in_out(t_pipe *data, int *i)
{
	if (*i % 2 == 0)
	{
		if (data_has_infile(data))
			dup2_fd_infile_std_in(data);
		else
			dup2(data->pipe1_fd[0], STDIN_FILENO); // 5, in
		if (data_has_outfile(data))
			dup2_fd_outfile_std_out(data);
	}
	else
	{
		if (data_has_infile(data))
			dup2_fd_infile_std_in(data);
		else
			dup2(data->pipe0_fd[0], STDIN_FILENO); // 3, in
		if (data_has_outfile(data))
			dup2_fd_outfile_std_out(data);
	}
}
