/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:38:37 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/09 15:15:35 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_cmd(char **cmd, int level)
// {
// 	for (int i = 0; i < level; i++)
// 		printf("    ");
// 	printf("Command:");
// 	for (int i = 0; cmd[i] != NULL; i++)
// 		printf(ORG " %s" RESET, cmd[i]);
// 	printf("\n");
// }

// void	print_assignment(t_assignment *assignments, int level)
// {
// 	for (int i = 0; i < level; i++)
// 		printf("    ");
// 	printf("Assignments:");
// 	for (t_assignment *tmp = assignments; tmp; tmp = tmp->next)
// 		printf(ORG " %s" RESET, tmp->word);
// 	printf("\n");
// }

// void	print_stdin_redirect(t_redirect	*stdin_redirect, int level)
// {
// 	for (int i = 0; i < level; i++)
// 		printf("    ");
// 	printf("stdin_redirect:");
// 	for (t_redirect *tmp = stdin_redirect; tmp; tmp = tmp->next)
// 		printf(ORG " %s" RESET, tmp->word);
// 	printf("\n");
// }

// void	print_stdout_redirect(t_redirect *stdout_redirect, int level)
// {
// 	for (int i = 0; i < level; i++)
// 		printf("    ");
// 	printf("stdout_redirect:");
// 	for (t_redirect *tmp = stdout_redirect; tmp; tmp = tmp->next)
// 		printf(ORG " %s" RESET, tmp->word);
// 	printf("\n");
// }

// void print_ast_node(t_ast_node *node, int level, char x)
// {
// 	if (x == 'x')
// 		printf("\n***************** AST ****************\n");
// 	if (node == NULL)
// 		return;
// 	for (int i = 0; i < level; i++)
// 		printf("  ");
// 	if (x == 'l')
// 		printf(BLUE "Left child:\n");
// 	if (x == 'r')
// 		printf(BLUE "Right child:\n" RESET);
// 	for (int i = 0; i < level; i++)
// 		printf("    ");
// 	if (node->type == AST_NODE_CMD)
// 	{
// 		printf(RED "Node type:" RESET ORG" AST_NODE_CMD\n" RESET);
// 		if (node->content)
// 		{
// 			for (int i = 0; i < level; i++)
// 				printf("    ");
// 			printf(RED "Content:\n"RESET);
// 			if (node->content->cmd)
// 				print_cmd(node->content->cmd, level);
// 			if (node->content->assignments)
// 				print_assignment(node->content->assignments, level);
// 			if (node->content->stdin_redirect)
// 				print_stdin_redirect(node->content->stdin_redirect, level);
// 			if (node->content->stdout_redirect)
// 				print_stdout_redirect(node->content->stdout_redirect, level);
// 		}
// 	}
// 	else if (node->type == AST_NODE_PIPE)
// 		printf(RED "Node type:"RESET ORG" AST_NODE_PIPE\n" RESET);
// 	print_ast_node(node->left, level + 1, 'l');
// 	print_ast_node(node->right, level + 1, 'r');
// }
