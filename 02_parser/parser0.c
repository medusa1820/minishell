/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:41:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/25 16:15:35 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// // #include "lexer.h"
// #include "parser.h"

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

t_ast_node	*create_command_node(t_ast_node_content *content)
{
	t_ast_node	*node;

	node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (!node)
	{
		perror ("Memory allocation error"); //error handeling
		exit(1);
	}
	node->type = AST_NODE_CMD;
	node->content = content;
	for (int i = 0; node->content->cmd[i]; i++)
		printf("\nnode:cmd content type:%d valu:%s\n",i, node->content->cmd[i]);	
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

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
	return (node);
}

t_redirect_type	redirect_type(char *tpye)
{
	t_redirect_type	type;

	if (ft_strncmp(tpye, "</0", 2))
		type = REDIRECT_STDIN;
	else if (ft_strncmp(tpye, ">/0", 2))
		type = REDIRECT_STDOUT;
	else if (ft_strncmp(tpye, "<</0", 3))
		type = REDIRECT_HERE_DOC;
	else if (ft_strncmp(tpye, ">>/0", 3))
		type = REDIRECT_STDOUT_APPEND;
	return (type);
}

t_parser_state	add_redirect(t_redirect **redirect, \
t_redirect *new_redirection)
{
	t_redirect		*last_redirection;

	if (redirect == NULL || new_redirection == NULL)
		return (PARSER_FAILURE);
	if (*redirect == NULL)
		*redirect = new_redirection;
	else
	{
		last_redirection = *redirect;
		while (last_redirection->next != NULL)
			last_redirection = last_redirection->next;
		last_redirection->next = new_redirection;
	}
	return (PARSER_SUCCESS);
}

t_parser_state	parse_redirection(t_ast_node_content **content, t_token **tokens, int *index, int *token_count)
{
	t_redirect		*new_redirection;
	t_redirect_type	type;
	t_parser_state	ret;
	printf("ok2\n");
	// (*index)--;
	new_redirection = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!new_redirection)
	{
		perror("Memory allocation error");
		return PARSER_FAILURE;
	}
	type = redirect_type((*tokens)[*index].value); // Set the type of redirection
	printf("type:%d\n", type);
	new_redirection->type = type;
	new_redirection->word = ft_strdup((*tokens)[*index + 1].value); // put next head in value of this node
	free((*tokens)[*index + 1].value);
	(*tokens)[*index + 1].value = NULL;
	new_redirection->next = NULL;
	if (type == REDIRECT_STDIN || type == REDIRECT_HERE_DOC)
		ret = add_redirect(&((*content)->stdin_redirect), new_redirection);
	if (type == REDIRECT_STDOUT || type == REDIRECT_STDOUT_APPEND)
		ret = add_redirect(&((*content)->stdout_redirect), new_redirection);
	if (ret == PARSER_FAILURE)
		return (PARSER_FAILURE);
	// printf("redirect:%s\n", (*content)->redirection->word);
	(*index)++;
	(*index)++;
	(*token_count)--;
	(*token_count)--;
	// free(new_redirection);
	// new_redirection = NULL;
	return PARSER_SUCCESS;
}

t_parser_state parse_assignment(t_ast_node_content **content, t_token **tokens, int *index, int *token_count)
{
	t_assignment *new_assignment = (t_assignment *)malloc(sizeof(t_assignment));
	t_assignment *last_assignment;

	// (*index)++;
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
	(*token_count)--;
	return PARSER_SUCCESS;
}

t_ast_node_content *parse_command_content(t_ast_node_content **content, t_token **tokens, int *token_count)
{
	int	head;
	int cmd_index;
	int	index;
	int tmp;
	t_parser_state ret;

	head = *token_count - 1;
	tmp = *token_count;
	cmd_index = 0;
	// printf(ORG"\ntokens_Numbers:%d -> tokens_count:%d\n\n"RESET, *token_count -1, *token_count);
	// if ((*tokens)[*token_count - 1].value)
	// 	printf(ORG"item:%d len:%d value:%s\n"RESET, (*token_count), (*tokens)->len, (*tokens)[*token_count -1].value);
	while (head >= 0)
	{
		if ((*tokens)[head].type == TOKEN_PIPE)
			break ;
		else
			cmd_index++;
		if ((head - 1) >= 0 && (*tokens)[head - 1].type == TOKEN_PIPE)
			break ;
		head--;
	}
		// && (*tokens)[head--].type != TOKEN_END) //check if --head or head--
	if (*token_count >= 0 && cmd_index < 1 && (*tokens)[*token_count - 1].type == TOKEN_PIPE)
	{
		// printf(ORG"\ntoken_count:%d -> %d\n\n"RESET, *token_count -1, *token_count);
		free(*content);
		*content = NULL;
		return NULL;
	}
	if (head < 0)
		head = 0;
	// for (int i = head; i < *token_count; i++)
	// 	printf("i:%d toekn:%s\n", i, (*tokens)[i].value);
	// printf("head:%d token_count:%d" ORG" cmd:%d\n"RESET, head, *token_count, cmd_index);
	// exit(1);
	// cmd_index++;
	(*content)->cmd = (char **)ft_calloc((++cmd_index), sizeof(char *));
	(*content)->cmd[cmd_index] = NULL;
	index = 0;
	printf("\nstart type:%d value:%s\n",(*tokens)[head].type, (*tokens)[head].value);
	while (head < tmp && (*tokens)[head].type != TOKEN_PIPE)
	{
				printf("in loop ok1\n");
		if ((*tokens)[head].value != NULL)
		{
			printf("start type:%d value:%s\n",(*tokens)[head].type, (*tokens)[head].value);
			if (tmp >= 2 && (*tokens)[head].type && (*tokens)[head].type == TOKEN_REDIRECT && \
				((*tokens)[head + 1].type == TOKEN_ASSIGNMENT ||\
				(*tokens)[head + 1].type == TOKEN_WORD ))
			{
				ret = parse_redirection(content, tokens, &head, token_count);
				printf("after redir type:%d valu:%s\n",(*tokens)[head].type, (*tokens)[head].value);
				if(ret == PARSER_SUCCESS && (*tokens)[head].type == TOKEN_ASSIGNMENT)
				{
					ret = parse_assignment(content, tokens, &head, token_count);
					printf("after assign type:%d valu:%s\n",(*tokens)[head].type, (*tokens)[head].value);
					// printf("ok2\n"); //probably continue
				}
				else if (ret == PARSER_SUCCESS && (*tokens)[head].type == TOKEN_WORD)
				{
					printf("after redir inside cmd type:%d valu:%s\n",(*tokens)[head].type, (*tokens)[head].value);
					(*content)->cmd[index++] = ft_strdup((*tokens)[head].value);
					free((*tokens)[head].value);
					(*tokens)[head].value = NULL;
					(*token_count)--;
				}
				// if ((*tokens)[*token_count].type == TOKEN_PIPE)
				// 	return (*content);
				head++;
				continue;
			}
			else
			{
				printf("cmd index:%d type:%d valu:%s\n", index, (*tokens)[head].type, (*tokens)[head].value);
				(*content)->cmd[index++] = ft_strdup((*tokens)[head].value);
				free((*tokens)[head].value);
				(*tokens)[head].value = NULL;
			}	
		}
		else
			(*content)->cmd[index] = NULL;
		(head)++;
		(*token_count)--;
	}
	return (*content);
}


// t_ast_node_content *paarse_command_content(t_ast_node_content **content, t_token **tokens, int *token_count)
// {
// 	int	current;
// 	int cmd_index;
// 	t_parser_state ret;
// 	current = *token_count;
// 	cmd_index = 0;
// 	if (*token_count >= 0 && (*tokens)[*token_count - 1].type == TOKEN_PIPE)
// 	{
// 		free(*content);
// 		*content = NULL;
// 		return NULL;
// 	}
// 	while (current > 0 && (*tokens)[--current].type != TOKEN_PIPE) //since token_count is one more than itrator
// 		cmd_index++;
// 	for (int i = current; i < *token_count; i++)
// 		printf("i:%d toekn:%s\n", i, (*tokens)[i].value);
// 	printf("currrent:%d token_count:%d\n", current, *token_count);
// 	(*content)->cmd = (char **)ft_calloc((cmd_index + 1), sizeof(char *));
// 	(*content)->cmd[cmd_index] = NULL;
// 	while (--cmd_index >= 0 && (*tokens)[*token_count - 1].type != TOKEN_PIPE)
// 	{
// 		if ((*tokens)[*token_count - 1].value != NULL)
// 		{
// 			printf("start type:%d value:%s\n",(*tokens)[*token_count - 1].type, (*tokens)[*token_count - 1].value);
// 			if (*token_count >= 2 && (*tokens)[*token_count - 2].type && (*tokens)[*token_count - 2].type == TOKEN_REDIRECT && 
// 				((*tokens)[*token_count - 1].type == TOKEN_ASSIGNMENT ||
// 				(*tokens)[*token_count - 1].type == TOKEN_WORD ))
// 			{
// 				// printf("ok1\n");
// 				if ((*tokens)[*token_count - 1].type == TOKEN_ASSIGNMENT)
// 				{
// 					ret = parse_assignment(content, tokens, token_count);
// 					printf("after assign type:%d valu:%s\n",(*tokens)[*token_count -1].type, (*tokens)[*token_count - 1].value);
// 					if(ret == PARSER_SUCCESS && (*tokens)[*token_count - 1].type == TOKEN_REDIRECT)
// 					{
// 						// printf("ok2\n");
// 						ret = parse_redirection(content, tokens, token_count);
// 					printf("after redir type:%d valu:%s\n",(*tokens)[*token_count - 1].type, (*tokens)[*token_count - 1].value);
// 					}
// 					// continue;
// 				}
// 				if ((*tokens)[*token_count].type == TOKEN_PIPE)
// 					return (*content);
// 				if ((*tokens)[*token_count - 1].type == TOKEN_WORD)
// 				{
// 					current = *token_count;
// 					while (current > 0 && (*tokens)[--current].type != TOKEN_PIPE) //since token_count is one more than itrator
// 						cmd_index++;
// 					printf("after redir inside cmd type:%d valu:%s\n",(*tokens)[*token_count - 1].type, (*tokens)[*token_count - 1].value);
// 					(*content)->cmd[cmd_index] = ft_strdup((*tokens)[*token_count - 1].value);
// 					free((*tokens)[*token_count - 1].value);
// 					(*tokens)[*token_count - 1].value = NULL;
// 				}
// 				(*token_count)--;
// 				continue;
// 			}
// 			else
// 			{
// 				(*content)->cmd[cmd_index] = ft_strdup((*tokens)[*token_count - 1].value);
// 				free((*tokens)[*token_count - 1].value);
// 				(*tokens)[*token_count - 1].value = NULL;
// 			}	
// 		}
// 		else
// 			(*content)->cmd[cmd_index] = NULL;
// 		(*token_count)--;
// 		// cmd_index--;
// 	}
// 	return (*content);
// }

t_ast_node *parse_command(t_token **tokens, int *token_count)
{
	t_ast_node_content *content;

	content = (t_ast_node_content *)ft_calloc(1, sizeof(t_ast_node_content));
	if (!content)
	{
		perror("Memory allocation error"); //error handling
		exit(1);
	}
	content->stdin_redirect = NULL;
	content->stdin_redirect = NULL;
	// content->redirection = NULL;
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

void free_ast(t_ast_node **node_ptr)
{
	if (!(*node_ptr))
		return;

	if ((*node_ptr)->type == AST_NODE_CMD)
	{
		if ((*node_ptr)->content)
		{
			if ((*node_ptr)->content->cmd)
			{
				int i = 0;
				while ((*node_ptr)->content->cmd[i] != NULL)
				{
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
	} else if ((*node_ptr)->type == AST_NODE_PIPE)
	{
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
				printf("Assignments:");
				for (t_assignment *tmp = node->content->assignments; tmp; tmp = tmp->next) {
					printf(ORG " %s" RESET, tmp->word);
				}
				printf("\n");
			}
			 if (node->content->stdin_redirect) {
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("stdin_redirect:");
				for (t_redirect *tmp = node->content->stdin_redirect; tmp; tmp = tmp->next) {
					printf(ORG " %s" RESET, tmp->word);
				}
				printf("\n");
			}
			if (node->content->stdout_redirect) {
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("stdout_redirect:");
				for (t_redirect *tmp = node->content->stdout_redirect; tmp; tmp = tmp->next) {
					printf(ORG " %s" RESET, tmp->word);
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