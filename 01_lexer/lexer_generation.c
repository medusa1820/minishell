/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_generation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:34 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/13 12:20:20 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_token *token)
{
	token->type = TOKEN_EMPTY;
	token->value = NULL;
	token->flag = false;
}

t_lexer_state	feed_tokens_array(t_minishell *sh, t_token *token)
{
	sh->token_len++;
	sh->head = sh->token_len - 1;
	sh->tokens = ft_realloc(sh->tokens, (sh->token_len - 1) * \
	sizeof(t_token), sh->token_len * sizeof(t_token));
	if (!sh->tokens)
		return (MALLOC_ERROR);
	sh->tokens[sh->token_len - 1] = *token;
	return (LEXER_SUCCESS);
}

t_lexer_state	checking_tokenizer(t_token *token, t_minishell *sh, const char **current)
{
	int			ret;

	ret = LEXER_SUCCESS;
	if (**current == '\'' && ret == LEXER_SUCCESS)
		ret = single_quote_handling(current, token);
	else if (**current == '"' && ret == LEXER_SUCCESS)
		ret = double_quote_handling(current, token);
	else if (ft_strchr(OPERAND, **current) && ret == LEXER_SUCCESS)
		ret = tokenize_pipe_and_redirector(current, token);
	else if (ft_strchr(WHITESPACE, **current) && ret == LEXER_SUCCESS)
	{
		// (*current)++;
		// return (LEXER_SUCCESS);
		ret = tokenize_space(current, token);
	}
	else if (ret == LEXER_SUCCESS)
		ret = tokenize_word(current, token);
	if (ret == LEXER_SUCCESS)
		ret = feed_tokens_array(sh, token);
	return (ret);
}

t_lexer_state	tokenize(t_minishell *sh, const char *line)
{
	int			ret;
	t_token		token;
	const char	*current;

	ret = LEXER_SUCCESS;
	init_token(&token);
	current = line;
	while (*current != '\0' && ret == LEXER_SUCCESS)
	{
		ret = checking_tokenizer(&token, sh, &current);
	}
	sh->free_lexer_token_len = sh->token_len;
	if (ret == LEXER_SUCCESS)
	{
		check_assignment(&(sh->tokens), sh->token_len);
		remove_empty_tokens(sh);
		print_tokenss(sh);
		printf("before expand--------\n");
		expander(sh);
		print_tokenss(sh);
		printf("before triming--------\n");
		trimming_tokens_type(sh);
		print_tokenss(sh);
		printf("before joining--------\n");
		joining_tokens(sh);
		sh->free_lexer_token_len = sh->token_len;
		print_tokenss(sh);
	}
	return (ret);
}
