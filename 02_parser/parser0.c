/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:41:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/14 22:19:18 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_ast_node *create_command_node(char **cmd) {
//     t_ast_node *node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
//     if (!node) {
//         perror("Memory allocation error");
//         exit(1);
//     }
//     node->type = AST_NODE_CMD;
//     node->content = (t_ast_node_content *)ft_calloc(1, sizeof(t_ast_node_content));
//     if (!node->content) {
//         perror("Memory allocation error");
//         exit(1);
//     }
//     node->content->cmd = cmd;
//     node->left = NULL;
//     node->right = NULL;
//     return node;
// }

t_ast_node *create_command_node(t_ast_node_content *content)
{
	t_ast_node *node;

	node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (!node) {
		perror("Memory allocation error"); //error handeling
		exit(1);
	}
	node->type = AST_NODE_CMD;
	node->content = content;
	node->left = NULL;
	node->right = NULL;
	return node;
}

t_ast_node *create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node *node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
	{
		perror("Memory allocation error"); //error handling
		exit(1);
	}
	node->type = AST_NODE_PIPE;
	node->content = NULL;
	node->left = left;
	node->right = right;
	return node;
}

t_ast_node_content *parse_command_content(t_ast_node_content **content, t_token **tokens, int *token_count)
{
	int	current;
	int cmd_index;

	current = *token_count;
	cmd_index = 0;
	if (*token_count >= 0 && (*tokens)[*token_count - 1].type == TOKEN_PIPE)
	{
		free(content);
		return NULL;
	}
	while (current-- > 0 && (*tokens)[current].type != TOKEN_PIPE) //since token_count is one more than itrator
		cmd_index++;
	(*content)->cmd = (char **)ft_calloc((cmd_index + 1), sizeof(char *));
	(*content)->cmd[cmd_index] = NULL;
	while (cmd_index-- > 0)
	{
 		(*content)->cmd[cmd_index] = ft_strdup((*tokens)[*token_count - 1].value);
		(*token_count)--;
	}
	return (*content);
}

t_ast_node *parse_command(t_token **tokens, int *token_count)
{
	t_ast_node_content *content;

	content = (t_ast_node_content *)malloc(sizeof(t_ast_node_content));
	if (!content)
	{
		perror("Memory allocation error"); //error handling
		exit(1);
	}
	content->stdin_redirect = NULL;
	content->stdout_redirect = NULL;
	content->assignments = NULL;
	content->cmd = NULL;
	parse_command_content(&content, tokens, token_count);
	if (content == NULL) {
		return NULL;  // Return NULL if command content is empty (due to PIPE)
	}
	return create_command_node(content);
}

t_ast_node *parse_pipeline(t_token **tokens, int *token_count)
{
	t_ast_node *left;
	t_ast_node *right;

	left = parse_command(tokens, token_count);

	if (*token_count > 0 && (*tokens)[*token_count - 1].type == TOKEN_PIPE) {
		(*token_count)--;  // Consume the pipe operator
		right = parse_pipeline(tokens, token_count);
		return create_pipe_node(left, right);
	}

	return left;
}

void free_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return;
	if (node->type == AST_NODE_CMD)
	{
		if (node->content)
		{
			if (node->content->cmd)
			{
				i = -1;
				while (node->content->cmd[++i] != NULL)
					free(node->content->cmd[i]);
				free(node->content->cmd);
			}
			free(node->content);
		}
	}
	else if (node->type == AST_NODE_PIPE)
	{
		free_ast(node->left);
		free_ast(node->right);
	}
	free(node);
}

void print_ast_node(t_ast_node *node, int level, char x) {
	if (node == NULL) {
		return;
	}
	if (x == 'l')
		printf(BLUE "Left child:\n");
	if (x == 'r')
		printf(BLUE "Right child:\n" RESET);
	for (int i = 0; i < level; i++)
		printf("    ");
	if (node->type == AST_NODE_CMD) {
		printf(RED "Node type:" RESET ORG" AST_NODE_CMD\n" RESET);
		if (node->content)
		{
			for (int i = 0; i < level; i++)
				printf("    ");
			printf(RED "Content:\n"RESET);
			if (node->content->cmd)
			{
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("Command:");
				for (int i = 0; node->content->cmd[i] != NULL; i++) {
					printf(ORG " %s" RESET, node->content->cmd[i]);
				}
				printf("\n");
			}
		}
	} else if (node->type == AST_NODE_PIPE) {
		printf(RED "Node type:"RESET ORG" AST_NODE_PIPE\n" RESET);
	}

	print_ast_node(node->left, level + 1, 'l');
	print_ast_node(node->right, level + 1, 'r');
}