/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:34 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/30 16:24:37 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *token_names[] = { //SHOULD REMOVE IT LATER ON
	"EMPTY",
	"SIN_QUOTE",
	"DUB_QUOTE",
	"REDIRECT",
	"PIPE",
	"WORD",
	"UNCL_QUO",
	"ASSIGNMNT",
	"END"
	// Add more names for additional token types if needed
};

void	print_tokens(t_minishell sh)
{
	printf("len:%d free_len:%d\n", sh.token_len, sh.free_lexer_token_len);
	for(int i = 0; i < sh.token_len; i++)
	{
		printf(BLUE "Token Type" RESET " : " ORG "%s" RESET, token_names[sh.tokens[i].type]);
		printf(RED "	Value" RESET " : " ORG "%s\n" RESET, sh.tokens[i].value);
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

void	token_unclosed(const char **current, t_token *token)
{
	token->type = TOKEN_UNCLOSED_Q;
	token->value = malloc(1); // Allocate memory for null-terminator
	token->value[0] = '\0';
	(*current)++;
	return ;
}

void	single_quote_handling(const char **current, t_token *token)
{
	int	len;

	len = 0;
	if ((*current)[1] == '\0')
		return (token_unclosed(current, token));
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
		token->type = TOKEN_UNCLOSED_Q;
	if (!token->value)
		token->type = TOKEN_EMPTY;
}
void double_quote_handling(const char **current, t_token *token)
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
		token->type = TOKEN_UNCLOSED_Q;
	if (!token->value)
		token->type = TOKEN_EMPTY;
}
void	tokenize_pipe_and_redirector(const char **current, t_token *token)
{
	token->type = TOKEN_REDIRECT;
	if ((**current == '<' && *(*current + 1) == '<') \
	|| (**current == '>' && *(*current + 1) == '>'))
	{
		token->value = ft_calloc(3, 1);
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
}
void	tokenize_word(const char **current, t_token *token)
{
	int	len;

	len = 0;
	token->type = TOKEN_WORD;
	token->value = ft_calloc(1, 1);
	while (!(ft_strchr(WHITESPACE, **current)) && \
	!(ft_strchr(OPERAND, **current) && **current != '\0'))
	{
		len++;
		token->value = ft_realloc(token->value, \
						ft_strlen(token->value), len + 1);
		token->value[len - 1] = **current;
		token->value[len] = '\0';
		(*current)++;
	}
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

void	feed_tokens_array(t_minishell *sh, t_token token)
{
	sh->token_len++;
	sh->head = sh->token_len - 1;
	sh->tokens = ft_realloc(sh->tokens, (sh->token_len - 1) * \
	sizeof(t_token), sh->token_len * sizeof(t_token));
	sh->tokens[sh->token_len - 1] = token;
}

void tokenize(t_minishell *sh, const char *line)
{
	const char	*current;
	t_token		token;

	current = line;
	while (*current != '\0')
	{
		if (*current == '\'')
			single_quote_handling(&current, &token);
		else if (*current == '"')
			double_quote_handling(&current, &token);
		else if (ft_strchr(OPERAND, *current))
			tokenize_pipe_and_redirector(&current, &token);
		else if (ft_strchr(WHITESPACE, *current))
		{
			current++;
			continue ;
		}
		else
			tokenize_word(&current, &token);
		feed_tokens_array(sh, token);
	}
	sh->free_lexer_token_len = sh->token_len;
	check_assignment(&(sh->tokens), sh->token_len);
}
