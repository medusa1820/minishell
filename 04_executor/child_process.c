/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:21:08 by musenov           #+#    #+#             */
/*   Updated: 2023/09/18 22:25:44 by musenov          ###   ########.fr       */
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




/*					FROM PIPEX

void	here_doc_open(t_pipex *data, char **argv)
{
	char	*buffer;
	int		fd_here_doc;

	fd_here_doc = open("here_doc_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_here_doc < 0)
		exit_error(errno, "Error creating temporary here_doc_file", data);
	ft_putstr_fd("here_doc>", STDOUT_FILENO);
	buffer = get_next_line(STDIN_FILENO);
	while (buffer)
	{
		if (ft_strlen(argv[2]) == ft_strlen(buffer) - 1 && \
		!ft_strncmp(buffer, argv[2], ft_strlen(argv[2])))
		{
			free(buffer);
			close(fd_here_doc);
			break ;
		}
		else
			ft_putstr_fd(buffer, fd_here_doc);
		free(buffer);
		ft_putstr_fd("here_doc>", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
	}
	close(fd_here_doc);
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
		// fprintf(stderr, "%d %d %d\n", data->fd_infile, data->fd_outfile, data->pipe0_fd[1]);
		close_pipe0_fds(data);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() first", data);
	}
}

bool	data_has_infile(t_pipe *data)
{
	return (data->fd_infile != STDIN_FILENO);
}

bool	data_has_outfile(t_pipe *data)
{
	return (data->fd_outfile != STDOUT_FILENO);
}

/*
void	first_pipe(t_pipe *data, char **envp, t_ast_node *node)
{
	t_redirect	*redirect;
	

	if (data->pid == 0)
	{
		if (node->content->stdin_redirect)
		{
			redirect = go_to_last_redirect(node->content->stdin_redirect);
			if (redirect->type == REDIRECT_STDIN)
			{
				data->fd_infile = open(redirect->word, O_RDONLY);
			}
			if (redirect->type == REDIRECT_HERE_DOC)
			{
				here_doc_open(data, redirect->word);
				data->fd_infile = open("here_doc_file", O_RDONLY);
				if (unlink("here_doc_file") == -1)
					exit_error(errno, "Error deleting here_doc temp file", data);
			}
			if (data->fd_infile < 0)
				exit_error(errno, "Error openning file", data);
			dup2(data->fd_infile, STDIN_FILENO);
			close(data->fd_infile);
		}
		if (node->content->cmd)
		{
			find_cmd_path(data, envp);
			// dup2(data->pipe0_fd[1], STDOUT_FILENO);
		}
		if (node->content->stdout_redirect)
		{
			redirect = go_to_last_redirect(node->content->stdout_redirect);
			if (redirect->type == REDIRECT_STDOUT)
			{
				data->fd_outfile = open(redirect->word, O_CREAT | O_RDWR | \
														O_TRUNC, 0644);
			}
			if (redirect->type == REDIRECT_STDOUT_APPEND)
			{
				data->fd_outfile = open(redirect->word, O_CREAT | O_RDWR | \
														O_APPEND, 0644);
			}
			if (data->fd_outfile < 0)
				exit_error(errno, "Error openning file", data);
			// dup2(data->fd_outfile, data->pipe0_fd[1]);
			dup2(data->fd_outfile, STDOUT_FILENO);
			close(data->fd_outfile);
		}
		close_pipe0_fds(data);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() first", data);
	}
}
*/

t_redirect	*go_to_last_redirect(t_redirect *head)
{
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void	here_doc_open(t_pipe *data, char *word)
{
	char	*buffer;
	int		fd_here_doc;

	fd_here_doc = open("here_doc_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_here_doc < 0)
		exit_error(errno, "Error creating temporary here_doc_file", data);
	ft_putstr_fd("here_doc>", STDOUT_FILENO);
	buffer = get_next_line(STDIN_FILENO);
	while (buffer)
	{
		if (ft_strlen(word) == ft_strlen(buffer) - 1 && \
		!ft_strncmp(buffer, word, ft_strlen(word)))
		{
			free(buffer);
			close(fd_here_doc);
			break ;
		}
		else
			ft_putstr_fd(buffer, fd_here_doc);
		free(buffer);
		ft_putstr_fd("here_doc>", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
	}
	close(fd_here_doc);
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
