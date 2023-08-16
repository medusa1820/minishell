/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:58:47 by musenov           #+#    #+#             */
/*   Updated: 2023/08/16 16:02:26 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirect(t_redirect *redirect, int level, char *type)
{
	for (int i = 0; i < level; i++) printf("    ");
	if (redirect) {
		printf("%s Redirect:\n", type);
		while (redirect) {
			for (int i = 0; i < level + 1; i++) printf("    ");
			printf("Type: %d, Word: %s\n", redirect->type, redirect->word ? redirect->word : "(null)");
			redirect = redirect->next;
		}
	} else {
		printf("%s Redirect: (null)\n", type);
	}
}

void	print_assignments(t_assignment *assignment, int level)
{
	for (int i = 0; i < level; i++) printf("    ");
	if (assignment) {
		printf("Assignments:\n");
		while (assignment) {
			for (int i = 0; i < level + 1; i++) printf("    ");
			printf("Word: %s\n", assignment->word ? assignment->word : "(null)");
			assignment = assignment->next;
		}
	} else {
		printf("Assignments: (null)\n");
	}
}

void	print_command(char **cmd, int level)
{
	for (int i = 0; i < level; i++) printf("    ");
	if (cmd) {
		printf("Command: ");
		while (*cmd) {
			printf("%s ", *cmd);
			cmd++;
		}
		printf("\n");
	} else {
		printf("Command: (null)\n");
	}
}


void	print_ast_tree0(t_ast_node *node, int level)
{
	for (int i = 0; i < level; i++)
		printf("    ");
	if (!node)
	{
		printf("Node: (null)\n");
		return;
	}
	// printf("Node type: %d\n", (int)node->type);
	printf("Node type: %s\n", getAstNodeTypeName(node->type));
	for (int i = 0; i < level; i++) printf("    ");
	if (node->content) {
		printf("Content:\n");
		print_command(node->content->cmd, level + 1);
		print_redirect(node->content->stdin_redirect, level + 1, "stdin");
		print_redirect(node->content->stdout_redirect, level + 1, "stdout");
		print_assignments(node->content->assignments, level + 1);
	} else {
		printf("Content: (null)\n");
	}
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("Left child:\n");
	print_ast_tree0(node->left, level + 1);
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("Right child:\n");
	print_ast_tree0(node->right, level + 1);
}

const char	*getAstNodeTypeName(t_ast_node_type type)
{
	switch (type) {
		case AST_NODE_CMD: return "AST_NODE_CMD";
		case AST_NODE_PIPE: return "AST_NODE_PIPE";
		default: return "Unknown";
	}
}
