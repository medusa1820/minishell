/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:41:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/21 13:21:14 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"

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

t_redirect_type	redirect_type(char *tpye)
{
	t_redirect_type	type;

	if(ft_strncmp(tpye, "</0", 2))
		type = REDIRECT_STDIN;
	else if(ft_strncmp(tpye, ">/0", 2))
		type = REDIRECT_STDOUT;
	else if(ft_strncmp(tpye, "<</0", 3))
		type = REDIRECT_HERE_DOC;
	else if(ft_strncmp(tpye, ">>/0", 3))
		type = REDIRECT_STDOUT_APPEND;
	return (type);
}

t_parser_state parse_redirection(t_ast_node_content **content, t_token **tokens, int *index)
{
	t_redirect *new_redirection = (t_redirect *)malloc(sizeof(t_redirect));
	t_redirect *last_redirection;

	if (!new_redirection)
	{
		perror("Memory allocation error");
		return PARSER_FAILURE;
	}
	new_redirection->type = redirect_type((*tokens)[*index].value); // Set the type of redirection
	new_redirection->word = ft_strdup((*tokens)[*index].value);
	free((*tokens)[*index].value);
	(*tokens)[*index].value = NULL;
	new_redirection->next = NULL;
	if ((*content)->redirection == NULL)
		(*content)->redirection = new_redirection;
	else
	{
		last_redirection = (*content)->redirection;
		while (last_redirection->next != NULL)
			last_redirection = last_redirection->next;
		last_redirection->next = new_redirection;
	}
	printf("redirect:%s\n", (*content)->redirection->word);
	(*index)++;
	return PARSER_SUCCESS;
}

t_parser_state parse_assignment(t_ast_node_content **content, t_token **tokens, int *index)
{
	t_assignment *new_assignment = (t_assignment *)malloc(sizeof(t_assignment));
	t_assignment *last_assignment;

	if (!new_assignment)
	{
		perror("Memory allocation error");
		return PARSER_FAILURE;
	}
	new_assignment->word = ft_strdup((*tokens)[*index].value);
	free((*tokens)[*index].value);
	(*tokens)[*index].value = NULL;
	new_assignment->next = NULL;
	if ((*content)->assignments == NULL)
		(*content)->assignments = new_assignment;
	else
	{
		last_assignment = (*content)->assignments;
		while (last_assignment->next != NULL)
			last_assignment = last_assignment->next;
		last_assignment->next = new_assignment;
	}
	(*index)++;
	return PARSER_SUCCESS;
}

t_parser_state	parse_cmd_word(t_ast_node_content **content, t_token **tokens, int *token_count, int *token_head)
{
	// int	tmp;
	int	cmd_index;

	// tmp = *token_count;
	cmd_index = 0;
	// while (tmp-- > *token_head && (*tokens)[tmp].type == TOKEN_WORD) //since token_count is one more than itrator
	// 	cmd_index++;
	(*content)->cmd = (char **)ft_calloc((token_count - token_head + 1), sizeof(char *));
	printf("cmd1 head:%d count:%d\n", *token_head, *token_count);
	while (cmd_index < (*token_count) && \
	(*tokens)[*token_head].type != TOKEN_REDIRECT && \
	(*tokens)[*token_head].type != TOKEN_PIPE)
	// while (++cmd_index < token_count - token_head + 1)
	{
		printf("i1:%d\n", *token_head);
		if ((*tokens)[*token_head].value != NULL)
		{
			(*content)->cmd[cmd_index] = ft_strdup((*tokens)[*token_head].value);
			free((*tokens)[*token_head].value);
			(*tokens)[*token_head].value = NULL;
		}
		else
			(*content)->cmd[cmd_index] = NULL;
		(*token_head)++;
		cmd_index++;
	}
	(*content)->cmd[cmd_index] = NULL;
	printf("cmd2 head:%d count:%d\n", *token_head, *token_count);
	return (PARSER_SUCCESS);
}

t_parser_state	parse_sufix_cmd(t_ast_node_content **content, t_token **tokens, int *token_count, int *token_head)
{
	t_parser_state	ret;

	printf("s1 head:%d count:%d\n", *token_head, *token_count);
	// while (current-- < *token_count && (*tokens)[current].type != TOKEN_WORD) //since token_count is one more than itrator
	// 	last++;
	ret = PARSER_FAILURE;
	if (*token_head == *token_count - 1) //check
		return (PARSER_SUCCESS);
	while(true && *token_head < *token_count)
	{
		if ((*tokens)[*token_head].type == TOKEN_REDIRECT && \
		((*tokens)[*token_head + 1].type == TOKEN_WORD || \
		(*tokens)[*token_head + 1].type == TOKEN_SINGLE_QUOTE || \
		(*tokens)[*token_head + 1].type == TOKEN_DOUBLE_QUOTE || \
		(*tokens)[*token_head + 1].type == TOKEN_ASSIGNMENT))
		{
			// exit(1);
		
			ret = parse_redirection(content, tokens, token_head);
			continue;
		}
		else if ((*tokens)[*token_head].type == TOKEN_ASSIGNMENT || \
		(*tokens)[*token_head].type == TOKEN_WORD || \
		(*tokens)[*token_head].type == TOKEN_DOUBLE_QUOTE || \
		(*tokens)[*token_head].type == TOKEN_SINGLE_QUOTE)
		{
			ret = parse_cmd_word(content, tokens, token_count, token_head); //check later about exitance of assignment here
			continue;
		}
		else
			break;
	}
	printf("s2 head:%d count:%d\n", *token_head, *token_count);
	return (ret);
}

t_parser_state	parse_prefix_cmd(t_ast_node_content **content, t_token **tokens, int *token_count, int *token_head)
{
	t_parser_state	ret;

	printf("pr1 head:%d count:%d\n", *token_head, *token_count);
	ret = PARSER_FAILURE;
	// while (current-- < *token_count && (*tokens)[current].type != TOKEN_WORD) //since token_count is one more than itrator
	// 	last++;
	while(*token_head < *token_count)
	{
		if (((*tokens)[*token_head].type == TOKEN_REDIRECT && \
		(*tokens)[*token_head + 1].type) && \
		((*tokens)[*token_head + 1].type == TOKEN_WORD || \
		(*tokens)[*token_head + 1].type == TOKEN_SINGLE_QUOTE || \
		(*tokens)[*token_head + 1].type == TOKEN_DOUBLE_QUOTE || \
		(*tokens)[*token_head + 1].type == TOKEN_ASSIGNMENT)) //later check variable of token,would better assign to the EOF and PIP
		{
			ret = parse_redirection(content, tokens, token_head);
			continue;
		}
		else if ((*tokens)[*token_head].type == TOKEN_ASSIGNMENT)
		{
			ret = parse_assignment(content, tokens, token_head);
			continue;
		}
		else
			break;
		if (ret == PARSER_FAILURE)
            return ret; // Return immediately on failure
	}
	printf("pr2 head:%d count:%d\n", *token_head, *token_count);
	return (ret);
}

t_parser_state parse_command_content(t_ast_node_content **content, t_token **tokens, int *token_count)
{
	t_parser_state	ret;
	int token_head;
	int	current;

	token_head = 0;
	ret = PARSER_FAILURE;
	if (*token_count >= 0 && (*tokens)[*token_count - 1].type == TOKEN_PIPE)
	{
		free(*content);
		printf("ok\n");
		*content = NULL;
		return (PARSER_SUCCESS);
	}
    printf("id:%d str:%s\n",(*token_count), (*tokens)[*token_count - 1].value);
    
	current = *token_count - 1;
	// cmd_index = 0;
	while (current > 0 && (*tokens)[current--].type != TOKEN_PIPE) //since token_count is one more than itrator
		// current--;
		// cmd_index++;
	token_head = current;
	printf("c1 head:%d current:%d value:%s count:%d\n", token_head, current, (*tokens)[token_head].value, *token_count);
	// while (token_head < *token_count)// &&  (*tokens)[token_head].type != TOKEN_PIPE)
	// {
		// ret = parse_prefix_cmd(content, tokens, token_count, &token_head);
		// if (ret == PARSER_FAILURE)
		// {
		// 	ret = parse_cmd_word(content, tokens, token_count, &token_head);
		// 	if (ret == PARSER_FAILURE)
		// 		return (ret);
		// }
		// else
		// {
		// 	if (parse_cmd_word(content, tokens, token_count, &token_head) == PARSER_FAILURE)
		// 		return (ret);
		// }
	// }
	ret = parse_prefix_cmd(content, tokens, token_count, &token_head);
    if (ret == PARSER_SUCCESS)
        ret = parse_cmd_word(content, tokens, token_count, &token_head);
    else
    {
        if (parse_cmd_word(content, tokens, token_count, &token_head) == PARSER_FAILURE)
            return ret; // Return the earlier error state
    }
		parse_sufix_cmd(content, tokens, token_count, &token_head);
	printf("c2 head:%d current:%d count:%d\n", token_head, current, *token_count);
	// (*token_count) = token_head;
	return (ret);
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

// void print_ast_node(t_ast_node *node, int level, char x)
// {
// 	if (x == 'x')
// 		printf("\n***************** AST ****************\n");
// 	if (node == NULL) {
// 		return;
// 	}
// 	for (int i = 0; i < level; i++)
// 		printf("  ");
// 	if (x == 'l')
// 		printf(BLUE "Left child:\n");
// 	if (x == 'r')
// 		printf(BLUE "Right child:\n" RESET);
// 	for (int i = 0; i < level; i++)
// 		printf("    ");
// 	if (node->type == AST_NODE_CMD) {
// 		printf(RED "Node type:" RESET ORG" AST_NODE_CMD\n" RESET);
// 		if (node->content)
// 		{
// 			for (int i = 0; i < level; i++)
// 				printf("    ");
// 			printf(RED "Content:\n"RESET);
// 			if (node->content->cmd)
// 			{
// 				for (int i = 0; i < level; i++)
// 					printf("    ");
// 				printf("Command:");
// 				for (int i = 0; node->content->cmd[i] != NULL; i++) {
// 					printf(ORG " %s" RESET, node->content->cmd[i]);
// 				}
// 				printf("\n");
// 			}
// 			if (node->content->assignments)
// 			{
// 				for (int i = 0; i < level; i++)
// 					printf("    ");
// 				printf("assignment:");
// 				for(t_assignment *tmp = node->content->assignments; tmp; tmp = tmp->next)
// 				{
// 					printf(ORG " %s" RESET, node->content->assignments->word);
// 				}
// 				printf("\n");
// 			}
// 		}
// 	} else if (node->type == AST_NODE_PIPE) {
// 		printf(RED "Node type:"RESET ORG" AST_NODE_PIPE\n" RESET);
// 	}

// 	print_ast_node(node->left, level + 1, 'l');
// 	print_ast_node(node->right, level + 1, 'r');
// }

void print_ast_node(t_ast_node *node, int level, char x)
{
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
        printf(RED "Node type:" RESET ORG " AST_NODE_CMD\n" RESET);

        if (node->content) {
            for (int i = 0; i < level; i++)
                printf("    ");
            printf(RED "Content:\n" RESET);

            if (node->content->cmd) {
                for (int i = 0; i < level; i++)
                    printf("    ");
                printf("Command:");
                for (int i = 0; node->content->cmd[i] != NULL; i++) {
                    printf(ORG " %s" RESET, node->content->cmd[i]);
                }
                printf("\n");
            }

            if (node->content->assignments) {
                for (int i = 0; i < level; i++)
                    printf("    ");
                printf("Assignments:");
                for (t_assignment *tmp = node->content->assignments; tmp; tmp = tmp->next) {
                    printf(ORG " %s" RESET, tmp->word);
                }
                printf("\n");
            }
            
            if (node->content->redirection) {
                for (int i = 0; i < level; i++)
                    printf("    ");
                printf("Redirections:");
                for (t_redirect *tmp = node->content->redirection; tmp; tmp = tmp->next) {
                    printf(ORG " %s" RESET, tmp->word);
                }
                printf("\n");
            }
        }
    } else if (node->type == AST_NODE_PIPE) {
        printf(RED "Node type:" RESET ORG " AST_NODE_PIPE\n" RESET);
    }

    print_ast_node(node->left, level + 1, 'l');
    print_ast_node(node->right, level + 1, 'r');
}