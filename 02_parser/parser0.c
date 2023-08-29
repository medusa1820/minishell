/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:41:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/29 20:10:37 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_shell(t_minishell *shell)
{
	shell->ast_root = NULL;
	shell->tokens = NULL;
	shell->free_lexer_token_len = 0;
	shell->token_len = 0;
	shell->tmp = 0;
	shell->head = 0;
	shell->index = 0;
	shell->cmd_index = 0;
	shell->line = NULL;
	return true;
}

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

t_redirect_type	redirect_type(char *str)
{
	t_redirect_type	type;

	if (str[0] == '>' && str[1] == '>')
		type = REDIRECT_STDOUT_APPEND;
	else if (str[0] == '<' && str[1] == '<')
		type = REDIRECT_HERE_DOC;
	else if (str[0] == '<' && str[1] == 0)
		type = REDIRECT_STDIN;
	else if (str[0] == '>' && str[1] == 0)
		type = REDIRECT_STDOUT;
	free(str);
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

t_parser_state	parse_redirection(t_ast_node_content **content, t_minishell *sh)
{
	t_redirect		*new_redirection;
	t_redirect_type	type;
	t_parser_state	ret;

	new_redirection = NULL;
	new_redirection = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!new_redirection)
		return (perror("Memory allocation error"), PARSER_FAILURE);
	type = redirect_type(sh->tokens[sh->head].value); // Set the type of redirection
	new_redirection->type = type;
	new_redirection->word = ft_strdup(sh->tokens[sh->head + 1].value); // put next head in value of this node
	free(sh->tokens[sh->head + 1].value);
	sh->tokens[sh->head + 1].value = NULL;
	new_redirection->next = NULL;
	if (type == REDIRECT_STDIN || type == REDIRECT_HERE_DOC)
		ret = add_redirect(&((*content)->stdin_redirect), new_redirection);
	if (type == REDIRECT_STDOUT || type == REDIRECT_STDOUT_APPEND)
		ret = add_redirect(&((*content)->stdout_redirect), new_redirection);
	if (ret == PARSER_FAILURE)
		return (PARSER_FAILURE);
	sh->head += 2;
	sh->token_len -= 2;
	return (PARSER_SUCCESS);
}

t_parser_state parse_assignment(t_ast_node_content **content, t_minishell *sh)
{
	t_assignment *new_assignment;;
	t_assignment *last_assignment;

	new_assignment = (t_assignment *)ft_calloc(1, sizeof(t_assignment));
	if (!new_assignment)
		return (perror("Memory allocation error"), PARSER_FAILURE);
	new_assignment->word = ft_strdup(sh->tokens[sh->head].value);
	if (!new_assignment->word)
		return (PARSER_FAILURE);
	free(sh->tokens[sh->head].value);
	sh->tokens[sh->head].value = NULL;
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
	sh->head++;
	sh->token_len--;
	return (PARSER_SUCCESS);
}

t_parser_state	parse_cmd_word(t_ast_node_content **content, t_minishell *sh)
{
	int	head_tmp;

	head_tmp = sh->head;
	while (sh->tokens[head_tmp++].type == TOKEN_WORD)
		sh->index++;
	(*content)->cmd = (char **) ft_calloc(sh->index + 2, sizeof(char *));
	sh->index = 0;
	while (sh->tokens[sh->head].type == TOKEN_WORD)
	{
		(*content)->cmd[sh->index] = ft_strdup(sh->tokens[sh->head].value);
		(*content)->cmd[sh->index + 1] = NULL;
		if (!(*content)->cmd[sh->index])
			return (PARSER_FAILURE);
		free(sh->tokens[sh->head].value);
		sh->tokens[sh->head].value = NULL;
		sh->head++;
		sh->token_len--;
		sh->index++;
	}
	sh->index = 0;	// exit(1);
	return (PARSER_SUCCESS);
}

t_parser_state	parse_sufix_cmd(t_ast_node_content **content, t_minishell *sh)
{
	t_parser_state	ret;

	ret = PARSER_FAILURE;
	while(true)
	{
		if (sh->tmp >= 2 && sh->tokens[sh->head].type && sh->tokens[sh->head].type == TOKEN_REDIRECT && \
				(sh->tokens[sh->head + 1].type == TOKEN_ASSIGNMENT ||\
				sh->tokens[sh->head + 1].type == TOKEN_WORD )) //later check variable of token,would better assign to the EOF and PIP
		{
			ret = parse_redirection(content, sh);
			continue;
		}
		else if (sh->tokens[sh->head].type == TOKEN_ASSIGNMENT || \
		sh->tokens[sh->head].type == TOKEN_WORD)
		{
			ret = parse_cmd_word(content, sh);
			continue;
		}
		else
			break;
	}
	return (ret);
}


t_parser_state	parse_prefix_cmd(t_ast_node_content **content, t_minishell *sh)
{
	t_parser_state	ret;

	ret = PARSER_FAILURE;
	while(true)
	{
		if (sh->tmp >= 2 && sh->tokens[sh->head].type && sh->tokens[sh->head].type == TOKEN_REDIRECT && \
				(sh->tokens[sh->head + 1].type == TOKEN_ASSIGNMENT ||\
				sh->tokens[sh->head + 1].type == TOKEN_WORD )) //later check variable of token,would better assign to the EOF and PIP
		{
			ret = parse_redirection(content, sh);
			continue;
		}
		else if (sh->tokens[sh->head].type == TOKEN_ASSIGNMENT)
		{
			ret = parse_assignment(content, sh);
			continue;
		}
		else
			break;
	}
	return (ret);
}
void	finding_segment_head(t_minishell *sh)
{
	sh->head = sh->token_len - 1;
	sh->tmp = sh->token_len;
	while (sh->head >= 0)
	{
		if (sh->tokens[sh->head].type == TOKEN_PIPE)
			break ;
		if ((sh->head - 1) >= 0 && sh->tokens[sh->head - 1].type == TOKEN_PIPE)
			break ;
		sh->head--;
	}
	if (sh->head < 0)
		sh->head = 0;
}

t_parser_state	parse_command_content(t_ast_node_content **content, t_minishell *sh)
{
	t_parser_state ret;

	if (sh->token_len >= 0 && sh->tokens[sh->token_len - 1].type == TOKEN_PIPE)
		return (free(*content),*content = NULL, PARSER_SUCCESS);
	finding_segment_head(sh);
	while (sh->head < sh->tmp )//&& sh->tokens[sh->head].type != TOKEN_PIPE)
	{
		ret = parse_prefix_cmd(content, sh);
		if (ret == PARSER_FAILURE)
		{	
			ret = parse_cmd_word(content, sh);
			if (ret == PARSER_FAILURE)
				return (ret);
		}
		else
		{		
			if (parse_cmd_word(content, sh) == PARSER_FAILURE)
				return (ret);
		}
		parse_sufix_cmd(content, sh);
	}
	return (PARSER_SUCCESS);
}

t_ast_node *parse_command(t_minishell *sh)
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
	content->assignments = NULL;
	content->cmd = NULL;
	parse_command_content(&content, sh);
	if (content == NULL)
		return NULL;  // Return NULL if command content is empty (due to PIPE)
	return create_command_node(content);
}

t_ast_node *parse_pipeline(t_minishell *sh)
{
	t_ast_node *left;
	t_ast_node *right;

	right = parse_command(sh);

	if (sh->token_len > 0 && sh->tokens[sh->token_len - 1].type == TOKEN_PIPE)
	{
		free(sh->tokens[sh->token_len - 1].value);
		sh->tokens[sh->token_len - 1].value = NULL;
		sh->token_len--;
		left = parse_pipeline(sh);
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
			if ((*node_ptr)->content->stdin_redirect)
			{
				t_redirect	*temp;
				while ((*node_ptr)->content->stdin_redirect != NULL)
				{
					temp = (*node_ptr)->content->stdin_redirect;
					(*node_ptr)->content->stdin_redirect = (*node_ptr)->content->stdin_redirect->next;
					free(temp->word);
					temp->word = NULL;
					free(temp);
					temp = NULL;
				}
				free((*node_ptr)->content->stdin_redirect);
				(*node_ptr)->content->stdin_redirect = NULL;
			}
			if ((*node_ptr)->content->stdout_redirect)
			{
				t_redirect	*temp;
				while ((*node_ptr)->content->stdout_redirect != NULL)
				{
					temp = (*node_ptr)->content->stdout_redirect;
					(*node_ptr)->content->stdout_redirect = (*node_ptr)->content->stdout_redirect->next;
					free(temp->word);
					temp->word = NULL;
					free(temp);
					temp = NULL;
				}
				free((*node_ptr)->content->stdout_redirect);
				(*node_ptr)->content->stdout_redirect = NULL;
			}
			if ((*node_ptr)->content->assignments)
			{
				t_assignment	*temp;
				while ((*node_ptr)->content->assignments != NULL)
				{
					temp = (*node_ptr)->content->assignments;
					(*node_ptr)->content->assignments = (*node_ptr)->content->assignments->next;
					free(temp->word);
					temp->word = NULL;
					free(temp);
					temp = NULL;
				}
				free((*node_ptr)->content->assignments);
				(*node_ptr)->content->assignments = NULL;
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

void print_ast_node(t_ast_node *node, int level, char x)
{
	if (x == 'x')
		printf("\n***************** AST ****************\n");
	if (node == NULL)
		return;
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
				for (int i = 0; node->content->cmd[i] != NULL; i++)
					printf(ORG " %s" RESET, node->content->cmd[i]);
				printf("\n");
			}
			if (node->content->assignments)
			{
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("Assignments:");
				for (t_assignment *tmp = node->content->assignments; tmp; tmp = tmp->next)
					printf(ORG " %s" RESET, tmp->word);
				printf("\n");
			}
			 if (node->content->stdin_redirect)
			 {
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("stdin_redirect:");
				for (t_redirect *tmp = node->content->stdin_redirect; tmp; tmp = tmp->next)
					printf(ORG " %s" RESET, tmp->word);
				printf("\n");
			}
			if (node->content->stdout_redirect)
			{
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("stdout_redirect:");
				for (t_redirect *tmp = node->content->stdout_redirect; tmp; tmp = tmp->next)
					printf(ORG " %s" RESET, tmp->word);
				printf("\n");
			}
		}
	}
	else if (node->type == AST_NODE_PIPE)
		printf(RED "Node type:"RESET ORG" AST_NODE_PIPE\n" RESET);
	print_ast_node(node->left, level + 1, 'l');
	print_ast_node(node->right, level + 1, 'r');
}
