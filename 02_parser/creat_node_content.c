/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_node_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:31:59 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/09 15:51:38 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_and_set_syntax_error_flag(t_minishell *sh, int ret)
{
	if (ret)
	{
		if (sh->head >= 0 && sh->head < sh->seg_end && \
			sh->tokens[sh->head].flag && \
			sh->tokens[sh->head].flag != TOKEN_WORD)
			sh->tokens[sh->head].flag = -2;
	}
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
	type = redirect_type(sh->tokens[sh->head].value);
	new_redirection->type = type;
	new_redirection->word = ft_strdup(sh->tokens[sh->head + 1].value);
	new_redirection->word_type = sh->tokens[sh->head + 1].flag;
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

t_parser_state	parse_assignment(t_ast_node_content **content, t_minishell *sh)
{
	t_assignment	*new_assignment;
	t_assignment	*last_assignment;

	new_assignment = (t_assignment *)ft_calloc(1, sizeof(t_assignment));
	if (!new_assignment)
		return (perror("Memory allocation error"), PARSER_FAILURE);
	new_assignment->word = ft_strdup(sh->tokens[sh->head].value);
	if (!new_assignment->word)
		return (PARSER_FAILURE);
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
	t_parser_state	ret;

	sh->cmd_count = sh->head - 1;
	ret = PARSER_FAILURE;
	if (sh->head < sh->seg_end && sh->tokens[sh->head].type != TOKEN_WORD)
	{
		check_and_set_syntax_error_flag(sh, ret);
		return (ret);
	}
	while (++sh->cmd_count < sh->seg_end && \
			sh->tokens[sh->cmd_count].type == TOKEN_WORD)
		sh->index++;
	if (sh->index)
	{
		(*content)->cmd = ft_realloc_strings((*content)->cmd, \
				count_strings((*content)->cmd), sh->index);
		sh->index = count_strings((*content)->cmd);
		while (sh->head < sh->seg_end && sh->tokens[sh->head].type == TOKEN_WORD)
		{
			(*content)->cmd[sh->index] = ft_strdup(sh->tokens[sh->head].value);
			(*content)->cmd[sh->index + 1] = NULL;
			if (!(*content)->cmd[sh->index++])
				return (PARSER_FAILURE);
			free(sh->tokens[sh->head].value);
			sh->tokens[sh->head++].value = NULL;
			sh->token_len--;
			ret = PARSER_SUCCESS;
		}
	}
	sh->index = 0;
	check_and_set_syntax_error_flag(sh, ret);
	return (ret);
}

t_parser_state	parse_sufix_cmd(t_ast_node_content **content, t_minishell *sh)
{
	t_parser_state	ret;

	ret = PARSER_FAILURE;
	while (true)
	{
		if (sh->seg_end >= 2 && sh->head + 1 < sh->seg_end && \
		sh->tokens[sh->head].type && \
		sh->tokens[sh->head].type == TOKEN_REDIRECT && \
		(sh->tokens[sh->head + 1].type == TOKEN_ASSIGNMENT || \
		sh->tokens[sh->head + 1].type == TOKEN_WORD))
		{
			ret = parse_redirection(content, sh);
			continue ;
		}
		else if (sh->head <= sh->token_len && (sh->tokens[sh->head].type == \
				TOKEN_ASSIGNMENT || sh->tokens[sh->head].type == TOKEN_WORD))
		{
			ret = feed_remained_cmd_tokens(content, sh);
			continue ;
		}
		else
			break ;
	}
	check_and_set_syntax_error_flag(sh, ret);
	return (ret);
}

t_parser_state	parse_prefix_cmd(t_ast_node_content **content, t_minishell *sh)
{
	t_parser_state	ret;

	ret = PARSER_FAILURE;
	while (true)
	{
		if (sh->seg_end >= 2 && sh->head + 1 < sh->seg_end && \
		sh->tokens[sh->head].type && \
		sh->tokens[sh->head].type == TOKEN_REDIRECT && \
		(sh->tokens[sh->head + 1].type == TOKEN_ASSIGNMENT || \
		sh->tokens[sh->head + 1].type == TOKEN_WORD))
		{
			ret = parse_redirection(content, sh);
			continue ;
		}
		else if (sh->head <= sh->token_len && \
				sh->tokens[sh->head].type == TOKEN_ASSIGNMENT)
		{
			ret = parse_assignment(content, sh);
			continue ;
		}
		else
			break ;
	}
	check_and_set_syntax_error_flag(sh, ret);
	return (ret);
}
