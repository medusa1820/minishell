/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:21:08 by musenov           #+#    #+#             */
/*   Updated: 2023/09/21 16:44:05 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_pipe(t_pipe *data, char **envp)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		close_pipe0_fds(data);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() first", data);
	}
	close_pipe0_fds(data);
}

/*							FROM PIPEX

void	get_fd_infile(char **argv, t_pipex *data)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{	
		here_doc_open(data, argv);
		data->fd_infile = open("here_doc_file", O_RDONLY);
	}
	else
	{
		data->fd_infile = open(argv[1], O_RDONLY);
	}
	if (data->fd_infile < 0)
		exit_error(errno, "Error openning file", data);
}
*/

/*					FROM PIPEX

void	first_cmd(t_pipex *data, char **envp, char **argv)
{
	if (data->pid == 0)
	{
		get_fd_infile(argv, data);
		find_cmd_path(data, envp);
		dup2(data->fd_infile, STDIN_FILENO);
		dup2(data->pipe0_fd[1], STDOUT_FILENO);
		close_pipe0_fds(data);
		if (data->here_doc)
		{
			if (unlink("here_doc_file") == -1)
				exit_error(errno, "Error deleting here_doc temp file", data);
		}
		close(data->fd_infile);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() first", data);
	}
}
*/

void	first_pipe(t_pipe *data, char **envp)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		if (data_has_infile(data))
		{
			dup2(data->fd_infile, STDIN_FILENO);
			close(data->fd_infile);
		}
		if (data_has_outfile(data))
		{
			dup2(data->fd_outfile, STDOUT_FILENO);
			close(data->fd_outfile);
		}
		else
			dup2(data->pipe0_fd[1], STDOUT_FILENO);
		close_pipe0_fds(data);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() first", data);
	}
}

/*					FROM PIPEX

void	middle_cmd(t_pipex *data, char **envp, int i)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		if (i % 2 == 0)
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
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() middle", data);
	}
	if (i % 2 == 0)
		close_pipe1_fds(data);
	else
		close_pipe0_fds(data);
}
*/

/*

void	middle_pipe(t_pipe *data, char **envp, int *i)
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
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() middle", data);
	}
	if (*i % 2 == 0)
		close_pipe1_fds(data);
	else
		close_pipe0_fds(data);
}

*/

void	middle_pipe(t_pipe *data, char **envp, int *i)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		if (*i % 2 == 0)
		{
			// dup2(data->pipe1_fd[0], STDIN_FILENO);
			// dup2(data->pipe0_fd[1], STDOUT_FILENO);
			if (data_has_infile(data))
			{
				dup2(data->fd_infile, STDIN_FILENO);
				close(data->fd_infile);
			}
			else
				dup2(data->pipe1_fd[0], STDIN_FILENO);
			if (data_has_outfile(data))
			{
				dup2(data->fd_outfile, STDOUT_FILENO);
				close(data->fd_outfile);
			}
			else
				dup2(data->pipe0_fd[1], STDOUT_FILENO);
		}
		else
		{
			// dup2(data->pipe0_fd[0], STDIN_FILENO);
			// dup2(data->pipe1_fd[1], STDOUT_FILENO);
			if (data_has_infile(data))
			{
				dup2(data->fd_infile, STDIN_FILENO);
				close(data->fd_infile);
			}
			else
				dup2(data->pipe0_fd[0], STDIN_FILENO);
			if (data_has_outfile(data))
			{
				dup2(data->fd_outfile, STDOUT_FILENO);
				close(data->fd_outfile);
			}
			else
				dup2(data->pipe1_fd[1], STDOUT_FILENO);
		}
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

/*					FROM PIPEX

void	last_cmd(t_pipex *data, char **envp, int i, char **argv)
{
	if (data->pid == 0)
	{
		get_fd_outfile(argv, data);
		find_cmd_path(data, envp);
		if (i % 2 == 0)
			dup2(data->pipe1_fd[0], STDIN_FILENO);
		else
			dup2(data->pipe0_fd[0], STDIN_FILENO);
		dup2(data->fd_outfile, STDOUT_FILENO);
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		close(data->fd_outfile);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() last", data);
	}
	close_pipe0_fds(data);
	close_pipe1_fds(data);
}
*/


/*

void	last_pipe(t_pipe *data, char **envp, int *i)
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
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() last", data);
	}
	close_pipe0_fds(data);
	close_pipe1_fds(data);
}

*/

void	last_pipe(t_pipe *data, char **envp, int *i)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		if (*i % 2 == 0)
		{
			// dup2(data->pipe1_fd[0], STDIN_FILENO);
			// dup2(data->pipe0_fd[1], STDOUT_FILENO);
			if (data_has_infile(data))
			{
				dup2(data->fd_infile, STDIN_FILENO);
				close(data->fd_infile);
			}
			else
				dup2(data->pipe1_fd[0], STDIN_FILENO);
			if (data_has_outfile(data))
			{
				dup2(data->fd_outfile, STDOUT_FILENO);
				close(data->fd_outfile);
			}
			// else
			// 	dup2(data->pipe0_fd[1], STDOUT_FILENO);
		}
		else
		{
			// dup2(data->pipe0_fd[0], STDIN_FILENO);
			// dup2(data->pipe1_fd[1], STDOUT_FILENO);
			if (data_has_infile(data))
			{
				dup2(data->fd_infile, STDIN_FILENO);
				close(data->fd_infile);
			}
			else
				dup2(data->pipe0_fd[0], STDIN_FILENO);
			if (data_has_outfile(data))
			{
				dup2(data->fd_outfile, STDOUT_FILENO);
				close(data->fd_outfile);
			}
			// else
			// 	dup2(data->pipe1_fd[1], STDOUT_FILENO);
		}
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() middle", data);
	}
	close_pipe0_fds(data);
	close_pipe1_fds(data);
}

