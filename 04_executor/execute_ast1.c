/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:27:01 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 21:07:03 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_redirections(t_pipe *data, t_ast_node *node, int *i)
{
	if (!handle_in_redirections(data, node))
	{
		(*i)++;
		return (false);
	}
	if (!handle_out_redirections(data, node))
	{
		(*i)++;
		return (false);
	}
	return (true);
}

bool	handle_in_redirections(t_pipe *data, t_ast_node *node)
{
	t_redirect	*redirect;

	redirect = node->content->stdin_redirect;
	data->fd_infile = STDIN_FILENO;
	while (redirect)
	{
		if (data->fd_infile != STDIN_FILENO)
			close(data->fd_infile);
		if (redirect->type == REDIRECT_STDIN)
			data->fd_infile = open(redirect->word, O_RDONLY);
		else if (redirect->type == REDIRECT_HERE_DOC)
		{
			here_doc_open(data, redirect->word, redirect->word_type);
			data->fd_infile = open("here_doc_file", O_RDONLY);
			if (unlink("here_doc_file") == -1)
				exit_error(errno, "Error deleting here_doc temp file", data);
		}
		if (data->fd_infile < 0)
		{
			error_do_next_iter(errno, "Error openning file", data);
			return (false);
		}
		redirect = redirect->next;
	}
	return (true);
}

bool	handle_out_redirections(t_pipe *data, t_ast_node *node)
{
	t_redirect	*redirect;

	redirect = node->content->stdout_redirect;
	data->fd_outfile = STDOUT_FILENO;
	while (redirect)
	{
		if (data->fd_outfile != STDOUT_FILENO)
			close(data->fd_outfile);
		if (redirect->type == REDIRECT_STDOUT)
			data->fd_outfile = open(redirect->word, O_CREAT | O_RDWR | \
													O_TRUNC, 0644);
		else if (redirect->type == REDIRECT_STDOUT_APPEND)
			data->fd_outfile = open(redirect->word, O_CREAT | O_RDWR | \
													O_APPEND, 0644);
		if (data->fd_outfile < 0)
		{
			error_do_next_iter(errno, "Error openning file", data);
			return (false);
		}
		redirect = redirect->next;
	}
	return (true);
}

bool	forker_no_pipe(t_pipe *data, char **envp, t_ast_node *node)
{
	int		saved_stdout;

	if (!handle_redirections_no_pipe(data, node))
		return (false);
	data->node = node;
	export_preps(data);
	if (data->cmd_split && is_builtin(data->cmd_split[0]))
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (data_has_outfile(data))
			dup2_fd_outfile_std_out(data);
		data->exit_code = execute_bltn(data->shell_data, data->cmd_split);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return (true);
	}
	data->pid = fork();
	if (data->pid == -1)
		return (false);
	else
	{
		no_pipe(data, envp);
		return (true);
	}
}

bool	handle_redirections_no_pipe(t_pipe *data, t_ast_node *node)
{
	if (!handle_in_redirections(data, node))
		return (false);
	if (!handle_out_redirections(data, node))
		return (false);
	return (true);
}
