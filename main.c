/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:46:03 by musenov           #+#    #+#             */
/*   Updated: 2023/08/01 22:03:05 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line;
	t_ast_node	*head;

	head = NULL;
	line = readline("minishell>");
	while (line)
	{
		add_history(line);
		printf("You entered: %s\n", line); // use the line
		rl_replace_line("", 0); // Clear the current input line 
		rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		line = readline("minishell>");
	}
	head = create_ast();
	return (0);
}

/*

ls -la | < main.c << E < Makefile  cat >> out_file | grep 1 | wc -c

ls -la | grep 1 | wc -c

*/

t_ast_node	*create_ast(void)
{
	char		**cmd;
	t_ast_node	*new_node_left;
	t_ast_node	*new_node_right;
	t_ast_node	*new_node_head;

	cmd = ft_split("ls -la", ' ');
	new_node_left = create_node();
	init_node(new_node_left, "AST_NODE_CMD", cmd, NULL, NULL);
	cmd = ft_split("grep 1", ' ');
	new_node_right = create_node();
	init_node(new_node_right, "AST_NODE_CMD", cmd, NULL, NULL);
	new_node_head = create_node();
	init_node(new_node_head, "AST_NODE_PIPE", NULL, new_node_left, new_node_right);
	return (new_node_head);
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

void	init_node(t_ast_node *new_node, char *node_type, char **cmd, \
				t_ast_node *new_node_left, t_ast_node *new_node_right)
{
	new_node->type = *node_type;
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
