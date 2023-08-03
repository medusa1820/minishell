/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:11:00 by musenov           #+#    #+#             */
/*   Updated: 2023/08/03 18:29:07 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast_node *node)
{
	t_assignment	*current_assignment;
	t_redirect		*current_redirect;
	t_redirect		*next_redirect;
	t_assignment	*next_assignment;
	char			**cmd_ptr;

	if (node == NULL)
		return ;
	// Free left and right subtrees
	free_ast(node->left);
	free_ast(node->right);
	// Free the content of the node
	if (node->content)
	{
		current_redirect = node->content->stdin_redirect;
		while (current_redirect)
		{
			next_redirect = current_redirect->next;
			free(current_redirect->word);
			free(current_redirect);
			current_redirect = next_redirect;
		}

		current_redirect = node->content->stdout_redirect;
		while (current_redirect)
		{
			next_redirect = current_redirect->next;
			free(current_redirect->word);
			free(current_redirect);
			current_redirect = next_redirect;
		}
		current_assignment = node->content->assignments;
		while (current_assignment)
		{
			next_assignment = current_assignment->next;
			free(current_assignment->word);
			free(current_assignment);
			current_assignment = next_assignment;
		}
		if (node->content->cmd)
		{
			cmd_ptr = node->content->cmd;
			while (*cmd_ptr)
			{
				free(*cmd_ptr);
				cmd_ptr++;
			}
			free(node->content->cmd);
		}
		free(node->content);
	}
	// Finally, free the node itself
	free(node);
}





/*

void	exit_error(int exit_code, char *error_msg, t_pipe *data)
{
	perror(error_msg);
	free_ast(head);
	exit(exit_code);
}

*/