/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:11:03 by musenov           #+#    #+#             */
/*   Updated: 2023/10/09 17:37:03 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

Traversing the AST will be carried out recursively, starting from head it 
will check if the left node is a cmd, if not, then it goes to left node of the
node it checked previously and checks if it is cmd, if not, goes continues 
this way until it finds the node which has cmd. If, finally, the node is 
cmd, then it executes that node and closes and returns to the calling 
function. The calling function will then execute the right node. After the 
right node executed then algorithm goes to out calling function and executes 
again the right node and goes this way until it reaches the head node.

*/

bool	execute_cmds(t_ast_node *head, int *i, t_pipe *data, char **envp)
{
	++(data->nr_of_cmd_nodes);
	if (head == NULL)
		return (false);
	if (head->type == AST_NODE_PIPE)
	{
	/*
		if (execute_cmds(head->left, i, data, envp))
			return (piper(data, i) && forker(data, i, envp, head->right));
		else
			return (false);
	*/
		execute_cmds(head->left, i, data, envp);
		return (piper(data, i) && forker(data, i, envp, head->right));
	}
	else
		return (piper(data, i) && forker(data, i, envp, head));
}

bool	piper(t_pipe *data, int *i)
{
	if (*i % 2 == 0)
	{
		if (pipe(data->pipe0_fd) == -1)
			return (false);
		return (true);
	}
	else
	{
		if (pipe(data->pipe1_fd) == -1)
			return (false);
		return (true);
	}
}

/*

Input and Output redirections are handled before forking otherwise at least 
here_doc will propagate to child processes

*/

bool	forker(t_pipe *data, int *i, char **envp, t_ast_node *node)
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
	data->pid = fork();
	if (data->pid == -1)
		return (false);
	else
	{
		data->cmd_split = node->content->cmd;
		if (*i == 0)
			first_pipe(data, envp);
		else if (*i == data->nr_of_cmd_nodes - 1)
			last_pipe(data, envp, i);
		else
			middle_pipe(data, envp, i);
		(*i)++;
		return (true);
	}
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
		{
			data->fd_infile = open(redirect->word, O_RDONLY);
		}
		else if (redirect->type == REDIRECT_HERE_DOC)
		{
			here_doc_open(data, redirect->word);
			data->fd_infile = open("here_doc_file", O_RDONLY);
			if (unlink("here_doc_file") == -1)
				exit_error(errno, "Error deleting here_doc temp file", data);
		}
		if (data->fd_infile < 0)
		{
			// exit_error(errno, "Error openning file", data);
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
		{
			data->fd_outfile = open(redirect->word, O_CREAT | O_RDWR | \
													O_TRUNC, 0644);
		}
		else if (redirect->type == REDIRECT_STDOUT_APPEND)
		{
			data->fd_outfile = open(redirect->word, O_CREAT | O_RDWR | \
													O_APPEND, 0644);
		}
		if (data->fd_outfile < 0)
		{
			// exit_error(errno, "Error openning file", data);
			error_do_next_iter(errno, "Error openning file", data);
			return (false);
		}
		redirect = redirect->next;
	}
	return (true);
}
