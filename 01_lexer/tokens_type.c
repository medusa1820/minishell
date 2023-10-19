/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:48:59 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/09 12:51:36 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer_state	single_quote_handling(const char **current, t_token *token)
{
	int	len;

	len = 0;
	token->type = TOKEN_SINGLE_QUOTE;
	if ((*current)[1] == '\0')
		return (token_unclosed(current, token), 1);
	token->value = ft_strdup("\0"); // Initialize the value to NULL before reallocating
	(*current)++; 
	while (**current != '\'' && **current != '\0')
	{
		len++;
		token->value = ft_realloc(token->value, len - 1, len + 1);
		token->value[len - 1] = **current;
		token->value[len] = '\0';
		(*current)++;
	}
	if (**current == '\'')
		(*current)++;
	else
		// token->type = TOKEN_UNCLOSED_Q;
		return (token_unclosed(current, token));
	if (token->value[0] == '\0')
		token->type = TOKEN_WORD;
	return (LEXER_SUCCESS);
}

t_lexer_state	double_quote_handling(const char **current, t_token *token)
{
	int	len;

	len = 0;
	token->type = TOKEN_DOUBLE_QUOTE;
	if ((*current)[1] == '\0')
		return (token_unclosed(current, token));
	token->value = ft_strdup("\0"); // Initialize the value to NULL before reallocating
	(*current)++; // Move past the opening double quote
	while (**current != '"' && **current != '\0')
	{
		len++;
		token->value = ft_realloc(token->value, len - 1, len + 1);
		token->value[len - 1] = **current;
		token->value[len] = '\0';
		(*current)++;
	}
	if (**current == '"')
		(*current)++;
	else
		// token->type = TOKEN_UNCLOSED_Q;
		return (token_unclosed(current, token));
	if (token->value[0] == '\0')
		token->type = TOKEN_WORD;
	return (LEXER_SUCCESS);
}

t_lexer_state	tokenize_pipe_and_redirector(const char **current, t_token *token)
{
	token->type = TOKEN_REDIRECT;
	if ((**current == '<' && *(*current + 1) == '<') \
	|| (**current == '>' && *(*current + 1) == '>'))
	{
		token->value = ft_calloc(3, 1);
		if (!token->value)
			return (MALLOC_ERROR);
		token->value[0] = **current;
		(*current)++;
		token->value[1] = **current;
		token->value[2] = '\0';
	}
	else
	{
		if (**current == '|')
			token->type = TOKEN_PIPE;
		token->value = ft_calloc(2, sizeof(char));
		token->value[0] = **current;
		token->value[1] = '\0';
	}
	(*current)++;
	return (LEXER_SUCCESS);
}

t_lexer_state	tokenize_space(const char **current, t_token *token)
{
	// int	len;

	// len = 0;
	token->type = TOKEN_SPACE;
	token->value = ft_strdup("\0");
	while ((ft_strchr(WHITESPACE, **current)) && \
		**current != '\0')
	{
		(*current)++;
	}
	return (LEXER_SUCCESS);
}

t_lexer_state	tokenize_word(const char **current, t_token *token)
{
	int	len;

	len = 0;
	token->type = TOKEN_WORD;
	token->value = ft_calloc(1, 1);
	if (!token->value)
		return (MALLOC_ERROR);
	while (!(ft_strchr(WHITESPACE, **current)) && \
	!(ft_strchr(OPERAND, **current) && **current != '\0'))
	{
		len++;
		token->value = ft_realloc(token->value, \
						ft_strlen(token->value), len + 1);
		if (!token->value)
			return (MALLOC_ERROR);
		token->value[len - 1] = **current;
		token->value[len] = '\0';
		(*current)++;
	}
	return (LEXER_SUCCESS);
}
