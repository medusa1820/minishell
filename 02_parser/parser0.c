/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:41:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/17 20:10:24 by nnavidd          ###   ########.fr       */
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
	if (!node)
	{
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

	node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
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

t_token_type	redirect_type(char *tpye)
{
	if(ft_strncmp(tpye, "</0", 2))
		return 1;
	else if(ft_strncmp(tpye, ">/0", 2))
		return 2;
	else if(ft_strncmp(tpye, "<</0", 3))
		return 3;
	else if(ft_strncmp(tpye, ">>/0", 3))
		return 4;
	return 0;
}


void	parse_redirection(t_ast_node_content **content, t_token **tokens, int *index)
{
	t_redirect	*head;
	t_redirect	*tmp;

	head = (*content)->redirection;
	tmp = (*content)->redirection;
	tmp->word = (char *)ft_calloc(ft_strlen((*tokens)[*index].value), sizeof(char));
	if (!(*content)->redirection)
	{
		tmp->type = redirect_type((*tokens)[*index].value);
		tmp->word = ft_strdup((*tokens)[*index].value);
		tmp->next = NULL;
		(*content)->redirection = tmp;
	}
	else
	{
		while ((*content)->redirection != NULL)
			(*content)->redirection = (*content)->redirection->next;
		(*content)->redirection->type = redirect_type((*tokens)[*index].value);
		(*content)->redirection->word = (*tokens)[*index].value;
		(*content)->redirection->next = NULL;
	}
	(*content)->redirection = head;

}

void	parse_assignment(t_ast_node_content **content, t_token **tokens, int *index)
{
	t_assignment	*head;

	head = (*content)->assignments;
	(*content)->assignments->word = (char *)ft_calloc(ft_strlen((*tokens)[*index].value), sizeof(char));
	if (!(*content)->assignments)
	{
		(*content)->assignments->word = ft_strdup((*tokens)[*index].value);
		(*content)->assignments->next = NULL;
	}
	else
	{
		while ((*content)->assignments != NULL)
			(*content)->assignments = (*content)->assignments->next;
		(*content)->assignments->word = (*tokens)[*index].value;
		(*content)->assignments->next = NULL;
	}
	(*content)->assignments = head;

}

void	prefix_cmd(t_ast_node_content **content, t_token **tokens, int *token_count, int *token_head)
{
	int	current;


	current = *token_head;
	printf("i ps1:%d\n", *token_head);
	// while (current-- < *token_count && (*tokens)[current].type != TOKEN_WORD) //since token_count is one more than itrator
	// 	last++;
	while(current < *token_count && (*tokens)[current].type != TOKEN_WORD)
	{
		if ((*tokens)[current].type == TOKEN_ASSIGNMENT)
		{
			parse_assignment(content, tokens, &current);
		}
		if ((*tokens)[current].type == TOKEN_REDIRECT)
		{
			parse_redirection(content, tokens, &current);
		}
		current++;
	}
	(*token_head) = current;
	printf("i ps2:%d\n", *token_head);
}


void	cmd(t_ast_node_content **content, t_token **tokens, int *token_count, int *token_head)
{
	int	tmp;
	int	cmd_index;

	tmp = *token_count;
	cmd_index = 0;
	while (tmp-- > *token_head && (*tokens)[tmp].type != TOKEN_PIPE) //since token_count is one more than itrator
		cmd_index++;
	(*content)->cmd = (char **)ft_calloc((cmd_index + 1), sizeof(char *));
	(*content)->cmd[cmd_index] = NULL;
	printf("i c1:%d\n", *token_head);
	while (cmd_index-- > *token_head)
	{
		printf("i1:%d\n", *token_head);
		if ((*tokens)[*token_count - 1].value != NULL)
		{
			(*content)->cmd[cmd_index] = ft_strdup((*tokens)[*token_count - 1].value);
			free((*tokens)[*token_count - 1].value);
			(*tokens)[*token_count - 1].value = NULL;
		}
		else
			(*content)->cmd[cmd_index] = NULL;
		(*token_count)--;
	}
	printf("i c2:%d\n", *token_head);
}

t_ast_node_content *parse_command_content(t_ast_node_content **content, t_token **tokens, int *token_count)
{
	int token_head;

	token_head = 0;
	if (*token_count >= 0 && (*tokens)[*token_count - 1].type == TOKEN_PIPE)
	{
		free(*content);
		*content = NULL;
		return NULL;
	}
	printf("i0:%d\n", token_head);
	prefix_cmd(content, tokens, token_count, &token_head);
	cmd(content, tokens, token_count, &token_head);
	// sufix_cmd(content, tokens, token_count, &cmd_index);
	// 	(*content)->cmd = (char **)ft_calloc((cmd_index + 1), sizeof(char *));
	// (*content)->cmd[cmd_index] = NULL;
	return (*content);
}

t_ast_node *parse_command(t_token **tokens, int *token_count)
{
	t_ast_node_content *content;

	content = (t_ast_node_content *)ft_calloc(1, sizeof(t_ast_node_content));
	if (!content)
	{
		perror("Memory allocation error"); //error handling
		exit(1);
	}
	// content->stdin_redirect = NULL;
	// content->stdout_redirect = NULL;
	content->redirection = NULL;
	content->assignments = NULL;
	content->cmd = NULL;
	parse_command_content(&content, tokens, token_count);
	if (content == NULL)
		return NULL;  // Return NULL if command content is empty (due to PIPE)
	return create_command_node(content);
}

t_ast_node *parse_pipeline(t_token **tokens, int *token_count)
{
	t_ast_node *left;
	t_ast_node *right;

	right = parse_command(tokens, token_count);

	if (*token_count > 0 && (*tokens)[*token_count - 1].type == TOKEN_PIPE)
	{
		free((*tokens)[*token_count - 1].value);
		(*tokens)[*token_count - 1].value = NULL;
		(*token_count)--;  // Consume the pipe operator
		left = parse_pipeline(tokens, token_count);
		return create_pipe_node(left, right);
	}
	return right;
}

void free_ast(t_ast_node **node_ptr) {
    if (!(*node_ptr))
        return;

    if ((*node_ptr)->type == AST_NODE_CMD) {
        if ((*node_ptr)->content) {
            if ((*node_ptr)->content->cmd) {
                int i = 0;
                while ((*node_ptr)->content->cmd[i] != NULL) {
                    free((*node_ptr)->content->cmd[i]);
                    (*node_ptr)->content->cmd[i] = NULL;
                    i++;
                }
                free((*node_ptr)->content->cmd);
                (*node_ptr)->content->cmd = NULL;
            }
            free((*node_ptr)->content);
            (*node_ptr)->content = NULL;
        }
    } else if ((*node_ptr)->type == AST_NODE_PIPE) {
        free_ast(&((*node_ptr)->left));
        free_ast(&((*node_ptr)->right));
        (*node_ptr)->left = NULL;
        (*node_ptr)->right = NULL;
    }

    free(*node_ptr);
    *node_ptr = NULL;
}

void print_ast_node(t_ast_node *node, int level, char x) {
	if (x == 'x')
		printf("\n***************** AST ****************\n");
	if (node == NULL) {
		return;
	}
	for (int i = 0; i < level; i++)
		printf("  ");
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
			if (node->content->assignments)
			{
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("assignment:");
				for(t_assignment *tmp = node->content->assignments; tmp; tmp = tmp->next)
				{
					printf(ORG " %s" RESET, node->content->assignments->word);
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