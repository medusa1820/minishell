/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:21:08 by musenov           #+#    #+#             */
/*   Updated: 2023/11/08 10:07:56 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_pipe(t_pipe *data, char **envp)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		if (data_has_infile(data))
			dup2_fd_infile_std_in(data);
		if (data_has_outfile(data))
			dup2_fd_outfile_std_out(data);
		close_pipe0_fds(data);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() no pipe", data);
	}
	close_pipe0_fds(data);
}

void	first_pipe(t_pipe *data, char **envp)
{
	if (data->pid == 0)
	{
		first_pipe_in_out(data);
		if (data->cmd_split && is_builtin(data->cmd_split[0]))
		{
			data->exit_code = execute_bltn(data->shell_data, data->cmd_split);
			close_pipe0_fds(data);
			exit(data->exit_code);
		}
		else
			find_cmd_path(data, envp);
		close_pipe0_fds(data);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() first", data);
	}
}

void	middle_pipe(t_pipe *data, char **envp, int *i)
{
	if (data->pid == 0)
	{
		middle_pipe_in_out(data, i);
		if (data->cmd_split && is_builtin(data->cmd_split[0]))
		{
			data->exit_code = execute_bltn(data->shell_data, data->cmd_split);
			close_pipe0_fds(data);
			close_pipe1_fds(data);
			exit(data->exit_code);
		}
		else
			find_cmd_path(data, envp);
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() middle", data);
	}
	if (*i % 2 == 0)
		close_pipe1_fds(data);
	else
		close_pipe0_fds(data);
}

void	last_pipe(t_pipe *data, char **envp, int *i)
{
	if (data->pid == 0)
	{
		last_pipe_in_out(data, i);
		if (data->cmd_split && is_builtin(data->cmd_split[0]))
		{
			data->exit_code = execute_bltn(data->shell_data, data->cmd_split);
			close_pipe0_fds(data);
			close_pipe1_fds(data);
			exit(data->exit_code);
		}
		else
			find_cmd_path(data, envp);
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() last", data);
	}
	close_pipe0_fds(data);
	close_pipe1_fds(data);
}
