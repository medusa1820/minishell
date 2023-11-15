/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:27:58 by nnavidd           #+#    #+#             */
/*   Updated: 2023/11/15 09:55:43 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_content(t_ast_node_content *content)
{
	if (content == NULL)
		return ;
	if (content->assignments)
		freeing_assignment(content->assignments);
	if (content->stdin_redirect)
		freeing_redirection(content->stdin_redirect);
	if (content->stdout_redirect)
		freeing_redirection(content->stdout_redirect);
	if (content->cmd)
		freeing_cmd(content->cmd);
}

void	freeing_cmd(char **cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	i = 0;
	// printf("hi 1\n");
	while (cmd[i] != NULL)
	{
		// printf("hi 2\n");
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	// printf("hi 3\n");
	cmd = NULL;
}

void	freeing_redirection(t_redirect *ptr)
{
	t_redirect	*temp;

	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp->word);
		temp->word = NULL;
		free(temp);
		temp = NULL;
	}
	free(ptr);
	ptr = NULL;
}

void	freeing_assignment(t_assignment *ptr)
{
	t_assignment	*temp;

	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp->word);
		temp->word = NULL;
		free(temp);
		temp = NULL;
	}
	free(ptr);
	ptr = NULL;
}
// HI "HI" ""HI "H"I

int	free_ast(t_ast_node *node_ptr)
{
	if (!node_ptr)
		return (1);
	if ((*node_ptr).type == AST_NODE_CMD)
	{
		if ((*node_ptr).content)
		{
			if ((*node_ptr).content->cmd)
				freeing_cmd((*node_ptr).content->cmd);
			if ((*node_ptr).content->stdin_redirect)
				freeing_redirection((*node_ptr).content->stdin_redirect);
			if ((*node_ptr).content->stdout_redirect)
				freeing_redirection((*node_ptr).content->stdout_redirect);
			if ((*node_ptr).content->assignments)
				freeing_assignment((*node_ptr).content->assignments);
		}
		free((*node_ptr).content);
	}
	else if ((*node_ptr).type == AST_NODE_PIPE)
	{
		free_ast((*node_ptr).left);
		free_ast((*node_ptr).right);
		(*node_ptr).left = NULL;
		(*node_ptr).right = NULL;
	}
	return (free(node_ptr), node_ptr = NULL, 0);
}
