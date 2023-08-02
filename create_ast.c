/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:00:49 by musenov           #+#    #+#             */
/*   Updated: 2023/08/02 19:37:45 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_ast(void)
{
	t_ast_node	*new_node_left;
	t_ast_node	*new_node_right;
	t_ast_node	*new_node_head;
	t_ast_node	*old_node_head;

	new_node_left = NULL;
	new_node_right = NULL;
	new_node_head = NULL;
	create_node_left("ls -la", &new_node_left);
	create_node_right("grep 1", &new_node_right);
	create_node_pipe(&new_node_head, new_node_left, new_node_right);
	create_node_right("wc -c", &new_node_right);
	old_node_head = new_node_head;
	create_node_pipe(&new_node_head, old_node_head, new_node_right);
	create_node_right("wc -l", &new_node_right);
	old_node_head = new_node_head;
	create_node_pipe(&new_node_head, old_node_head, new_node_right);

	return (new_node_head);
}

void	create_node_left(char *cmd_str, t_ast_node **new_node_left)
{
	char		**cmd;

	cmd = ft_split(cmd_str, ' ');
	*new_node_left = create_node();
	init_node(*new_node_left, AST_NODE_CMD, cmd, NULL, NULL);
}

void	create_node_right(char *cmd_str, t_ast_node **new_node_right)
{
	char		**cmd;

	cmd = ft_split(cmd_str, ' ');
	*new_node_right = create_node();
	init_node(*new_node_right, AST_NODE_CMD, cmd, NULL, NULL);
}

void	create_node_pipe(t_ast_node **new_node_head, \
						t_ast_node *new_node_left, t_ast_node *new_node_right)
{
	*new_node_head = create_node();
	init_node(*new_node_head, AST_NODE_PIPE, NULL, \
	new_node_left, new_node_right);
}

t_ast_node	*create_node(void)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	// new_node->type = NULL;
	new_node->content = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	init_node(t_ast_node *new_node, t_ast_node_type node_type, char **cmd, \
				t_ast_node *new_node_left, t_ast_node *new_node_right)
{
	new_node->type = node_type;
	if (cmd)
	{
		new_node->content = create_node_content();
		init_node_content(cmd, new_node);
	}
	else
	{
		new_node->left = new_node_left;
		new_node->right = new_node_right;
	}
}

t_ast_node_content	*create_node_content(void)
{
	t_ast_node_content	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	new_node->stdin_redirect = NULL;
	new_node->stdout_redirect = NULL;
	new_node->assignments = NULL;
	new_node->cmd = NULL;
	return (new_node);
}

void	init_node_content(char **cmd, t_ast_node *new_node)
{
	new_node->content->cmd = cmd;
}
