/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:11:03 by musenov           #+#    #+#             */
/*   Updated: 2023/09/13 20:44:52 by musenov          ###   ########.fr       */
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
	// printf("nr_of_cmd_nodes = %d\n", ++(data->nr_of_cmd_nodes));
	++(data->nr_of_cmd_nodes);
	// printf("\n");
	if (head == NULL)
		return (false);
	if (head->type == AST_NODE_PIPE)
	{
		if (execute_cmds(head->left, i, data, envp))
		{
			// print_2d_array(head->right->content->cmd);
			// printf("i = %d\n", (*i));
			return (piper(data, i) && forker(data, i, envp, head->right));
		}
		else
		{
			return (false);
		}
	}
	else
	{
		// print_2d_array(head->content->cmd);
		// printf("i = %d\n", (*i));
		return (piper(data, i) && forker(data, i, envp, head));
	}
}

void	print_2d_array(char **cmd)
{
	printf("content->cmd: ");
	while (*cmd)
	{
		printf("%s ", *cmd);
		cmd++;
	}
	printf("\n");
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

bool	forker(t_pipe *data, int *i, char **envp, t_ast_node *head)
{
	// printf("nr_of_cmd_nodes = %d\n", data->nr_of_cmd_nodes);
	data->pid = fork();
	if (data->pid == -1)
		return (false);
	else
	{
		data->cmd_split = head->content->cmd;
		if (*i == 0)
			first_cmd(data, envp);
		else if (*i == data->nr_of_cmd_nodes - 1)
			last_cmd(data, envp, i);
		else
			middle_cmd(data, envp, i);
		(*i)++;
		return (true);
	}
}


bool	forker_one_cmd(t_pipe *data, char **envp, t_ast_node *head)
{
	// printf("nr_of_cmd_nodes = %d\n", data->nr_of_cmd_nodes);
	data->pid = fork();
	if (data->pid == -1)
		return (false);
	else
	{
		data->cmd_split = head->content->cmd;
		first_cmd_one_cmd(data, envp);
		return (true);
	}
}
