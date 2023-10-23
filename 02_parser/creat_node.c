/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:41:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/14 18:25:34 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
// HI "HI" ""HI "H"I

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
		parse_sufix_cmd(content, sh);
	}
	return (PARSER_SUCCESS);
}

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
	content->stdin_redirect = NULL;
	content->stdin_redirect = NULL;
	content->assignments = NULL;
	content->cmd = NULL;
	ret = parse_command_content(&content, sh);
	if (ret)
	{
		sh->data->exit_code = 2;
		print_error2(NULL, 2, "syntax error near unexpected token `", sh);
		free_content(content);
	}
	if (content == NULL || ret)
		return (free(content), NULL);
	return (create_command_node(content));
}

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
			return (NULL);
		return (create_pipe_node(left, right));
	}
	else if (right == NULL)
		return (NULL);
	return (right);
}
