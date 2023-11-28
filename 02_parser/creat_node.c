/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:41:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/11/27 15:42:57 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function creates a CMD node according to the content that is received.*/

t_ast_node	*create_command_node(t_ast_node_content *content)
{
	t_ast_node	*node;

	node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (!node)
	{
		perror ("Memory allocation error");
		exit(1);
	}
	node->type = AST_NODE_CMD;
	node->content = content;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/* This function creates a pipe node according to the left and right node.*/

t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (!node)
	{
		perror("Memory allocation error");
		exit(1);
	}
	node->type = AST_NODE_PIPE;
	node->content = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

/* This function first finds the first command in each segment. The segment is
meant each part that only cmds are included, that could be pointed to any cmds
between each pipe or before/after the first/last pipe. Then parsing the cmds 
in each segments according to the tokens which are included, by considering the
prefix elements, command itself, and suffix elements that should be assigned to
variables inside the AST. The AST has two types of node CMD, and pipe.
Each CMD node is included of 4 types of contents: assignment, cmd, and redirects.
All this 4 types, initiates through prefix, cmd, and suffix functions.*/

t_parser_state	parse_command_content(t_ast_node_content **content, \
																t_minishell *sh)
{
	t_parser_state	ret;

	if (sh->token_len == 0 || (sh->token_len > 0 && \
		sh->tokens[sh->token_len - 1].type == TOKEN_PIPE))
		return (free(*content),*content = NULL, PARSER_SYNTAX_ERROR);
	finding_segment_head(sh);
	while (sh->head < sh->seg_end)
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
			if (parse_cmd_word(content, sh) == PARSER_FAILURE \
			&& sh->head == sh->seg_end)
				return (ret);
		}
		parse_suffix_cmd(content, sh);
	}
	return (PARSER_SUCCESS);
}

/* This function initiate a template of a content of a CMD node, and initiates
it by parse_command_content function, then pass it this initiated content to 
create_command_node function to create a node of CMD type.*/

t_ast_node	*parse_command(t_minishell *sh)
{
	int					ret;
	t_ast_node_content	*content;

	content = (t_ast_node_content *)ft_calloc(1, sizeof(t_ast_node_content));
	if (!content)
	{
		perror("Memory allocation error");
		exit(1);
	}
	content->stdout_redirect = NULL;
	content->stdin_redirect = NULL;
	content->assignments = NULL;
	content->cmd = NULL;
	ret = parse_command_content(&content, sh);
	if (ret)
	{
		sh->data->exit_code = 2;
		print_error2(NULL, "syntax error near unexpected token `", sh);
		free_content(content);
	}
	if (content == NULL || ret)
		return (free(content), NULL);
	return (create_command_node(content));
}

/*This function parsing commands according to the tokens recursively,
and assign them to left and right node. At the end it creates a pipe node in case
of both left and right nodes assigned correctly.*/

t_ast_node	*parse_pipeline(t_minishell *sh)
{
	t_ast_node	*left;
	t_ast_node	*right;

	right = parse_command(sh);
	if (sh->token_len > 0 && right != NULL && \
		sh->tokens[sh->token_len - 1].type == TOKEN_PIPE)
	{
		free(sh->tokens[sh->token_len - 1].value);
		sh->tokens[sh->token_len - 1].value = NULL;
		sh->token_len--;
		left = parse_pipeline(sh);
		if (left == NULL)
		{
			if (right)
				free_ast(right);
			return (NULL);
		}
		return (create_pipe_node(left, right));
	}
	else if (right == NULL)
		return (NULL);
	return (right);
}
