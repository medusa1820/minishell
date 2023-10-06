/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:34 by nnavidd           #+#    #+#             */
/*   Updated: 2023/09/11 20:43:34 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_minishell sh)
{
	const char	*token_names[9];
	int			i;

	token_names[0] = "EMPTY";
	token_names[1] = "SIN_QUOTE";
	token_names[2] = "DUB_QUOTE";
	token_names[3] = "REDIRECT";
	token_names[4] = "PIPE";
	token_names[5] = "WORD";
	token_names[6] = "UNCL_QUO";
	token_names[7] = "ASSIGNMNT";
	token_names[8] = "END";
	i = 0;
	while (i < sh.token_len)
	{
		printf(BLUE "Token Type" RESET " : " ORG "%s" RESET, \
		token_names[sh.tokens[i].type]);
		printf(RED "	Value" RESET " : " ORG "%s\n" RESET, \
		sh.tokens[i++].value);
	}
}

void	free_tokens(t_minishell *sh)
{
	int	i;

	i = -1;
	while (++i < (*sh).free_lexer_token_len)
	{
		if ((*sh).tokens[i].value)
		{
			free((*sh).tokens[i].value);
			(*sh).tokens[i].value = NULL;
		}
	}
	free((*sh).tokens);
	(*sh).tokens = NULL;
	(*sh).token_len = 0;
	(*sh).free_lexer_token_len = 0;
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		ptr = NULL;
		return (NULL);
	}
	if (ptr == NULL)
		return (ft_calloc(1, new_size));
	new_ptr = ft_calloc(1, new_size);
	if (new_ptr == NULL)
		return (ptr);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}

t_lexer_state	token_unclosed(const char **current, t_token *token)
{
	int	ret;

	ret = UNCLOSED_QUOTE;
	token->type = TOKEN_UNCLOSED_Q;
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	(*current)++;
	return (ret);
}

t_lexer_state	single_quote_handling(const char **current, t_token *token)
{
	int	len;

	len = 0;
	if ((*current)[1] == '\0')
		return (token_unclosed(current, token), 1);
	token->type = TOKEN_SINGLE_QUOTE;
	token->value = NULL;
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
	if (!token->value)
		token->type = TOKEN_EMPTY;
	return (LEXER_SUCCESS);
}
t_lexer_state	double_quote_handling(const char **current, t_token *token)
{
	int	len;

	len = 0;
	if ((*current)[1] == '\0')
		return (token_unclosed(current, token));
	token->type = TOKEN_DOUBLE_QUOTE;
	token->value = NULL; // Initialize the value to NULL before reallocating
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
	if (!token->value)
		token->type = TOKEN_EMPTY;
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
void	check_assignment(t_token **tokens, int token_count)
{
	int			i;
	int			j;
	const char	*word;

	i = -1;
	while (++i < token_count)
	{
		if ((*tokens)[i].type == TOKEN_WORD || \
			(*tokens)[i].type == TOKEN_SINGLE_QUOTE
			|| (*tokens)[i].type == TOKEN_DOUBLE_QUOTE)
		{
			word = (*tokens)[i].value;
			if (!ft_isalpha(*word) && *word != '_' && \
				ft_strchr(word, '=') && ft_strchr(word, '=') != word)
				continue ;
			j = -1;
			while (word[++j] != '=')
			{
				if (!ft_isalnum(word[j]) && word[j] != '_')
					break ;
			}
			if (word[j] == '=' && (*tokens)[i].type != TOKEN_ASSIGNMENT)
				(*tokens)[i].type = TOKEN_ASSIGNMENT;
		}
	}
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
		(*current)++;
		return (LEXER_SUCCESS);
	}
	else if (ret == LEXER_SUCCESS)
		ret = tokenize_word(current, token);
	if (ret == LEXER_SUCCESS)
		ret = feed_tokens_array(sh, token);
	return (ret);
}

void	init_token(t_token *token)
{
	token->type = TOKEN_EMPTY;
	token->value = NULL;
	token->flag = false;
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
		check_assignment(&(sh->tokens), sh->token_len);
	return (ret);
}