/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:11:03 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 21:05:34 by musenov          ###   ########.fr       */
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

/*

when the last fork is reached, there is no need to pipe, therefore if j == 1
then return (forker(data, i, envp, head->right))

*/

bool	execute_cmds(t_ast_node *head, int *i, t_pipe *data, char **envp)
{
	int		j;

	j = ++(data->nr_of_cmd_nodes);
	if (head == NULL)
		return (false);
	if (head->type == AST_NODE_PIPE)
	{
		execute_cmds(head->left, i, data, envp);
		if (j == 1)
			return (forker(data, i, envp, head->right));
		else
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
	if (!handle_redirections(data, node, i))
		return (false);
	data->pid = fork();
	if (data->pid == -1)
		return (false);
	else
	{
		data->node = node;
		export_preps(data);
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

void	export_preps(t_pipe *data)
{
	int				count_assgnmnts;
	int				i;
	t_assignment	*assignment_iter;

	data->cmd_splited = false;
	count_assgnmnts = count_nmbr_assignments(data->node);
	if (data->node->content->cmd && \
		ft_strncmp(data->node->content->cmd[0], "export", 7) == 0 && \
		count_assgnmnts != 0)
	{
		data->cmd_split = (char **) malloc (sizeof(char *) * \
							(1 + count_assgnmnts + 1));
		data->cmd_split[0] = ft_strdup(data->node->content->cmd[0]);
		i = 1;
		assignment_iter = data->node->content->assignments;
		while (i <= count_assgnmnts)
		{
			data->cmd_split[i++] = ft_strdup(assignment_iter->word);
			assignment_iter = assignment_iter->next;
		}
		data->cmd_split[i] = NULL;
		data->cmd_splited = true;
	}
	else
		data->cmd_split = data->node->content->cmd;
}

int	count_nmbr_assignments(t_ast_node *head)
{
	t_assignment	*assignment_iter;
	int				count_assignments;

	count_assignments = 0;
	assignment_iter = head->content->assignments;
	while (assignment_iter)
	{
		assignment_iter = assignment_iter->next;
		count_assignments++;
	}
	return (count_assignments);
}
