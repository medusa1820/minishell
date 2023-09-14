/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:21:08 by musenov           #+#    #+#             */
/*   Updated: 2023/09/14 11:20:32 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_cmd_one_cmd(t_pipe *data, char **envp)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		// dup2(data->pipe0_fd[1], STDOUT_FILENO);
		close_pipe0_fds(data);
		// execve(data->cmd_path, data->cmd_split, envp);
		// exit(127);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() first", data);
	}
	close_pipe0_fds(data);
}

void	first_cmd(t_pipe *data, char **envp)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		dup2(data->pipe0_fd[1], STDOUT_FILENO);
		close_pipe0_fds(data);
		// execve(data->cmd_path, data->cmd_split, envp);
		/*
		if (data->here_doc)
		{
			if (unlink("here_doc_file") == -1)
				exit_error(errno, "Error deleting here_doc temp file", data);
		}
		close(data->fd_infile);
		*/
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() first", data);
	}
}

void	middle_cmd(t_pipe *data, char **envp, int *i)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		if (*i % 2 == 0)
		{
			dup2(data->pipe1_fd[0], STDIN_FILENO);
			dup2(data->pipe0_fd[1], STDOUT_FILENO);
		}
		else
		{
			dup2(data->pipe0_fd[0], STDIN_FILENO);
			dup2(data->pipe1_fd[1], STDOUT_FILENO);
		}
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		execve(data->cmd_path, data->cmd_split, envp);
		// exit(127);
	}
	if (*i % 2 == 0)
		close_pipe1_fds(data);
	else
		close_pipe0_fds(data);
}

void	last_cmd(t_pipe *data, char **envp, int *i)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		if (*i % 2 == 0)
		{
			dup2(data->pipe1_fd[0], STDIN_FILENO);
		}
		else
		{
			dup2(data->pipe0_fd[0], STDIN_FILENO);
		}
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		execve(data->cmd_path, data->cmd_split, envp);
		// exit(127);
	}
	close_pipe0_fds(data);
	close_pipe1_fds(data);
}
