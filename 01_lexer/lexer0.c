/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:34 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/26 09:15:27 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parser.h"
// #include "lexer.h"
#include "minishell.h"

const char *token_names[] = {
	"WORD",
	"SIN_QUOTE",
	"DUB_QUOTE",
	"REDIRECT",
	"PIPE",
	"EMPTY",
	"UNCL_QUO",
	"ASSIGNMNT",
	"END"
	// Add more names for additional token types if needed
};

void	print_tokens(t_token *tokens, int token_count)
{
		for(int i = 0; i < token_count; i++)
		{
				printf(BLUE "Token Type" RESET " : " ORG "%s" RESET, token_names[tokens[i].type]);
				printf(RED "	Value" RESET " : " ORG "%s\n" RESET, tokens[i].value);
		}

}

void	free_tokens(t_token **tokens, int *token_count)
{
	int	i;

	i = -1;
	while (++i < *token_count)
	{
		if((*tokens)[i].value)
		{
			free((*tokens)[i].value);
			(*tokens)[i].value = NULL;
		}
	}
	free(*tokens);
	*tokens = NULL;
	*token_count = 0;
}

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

 	if (new_size == 0)
	{
		free(ptr);
		ptr = NULL;
		return NULL;
	}
	if (ptr == NULL)
		return (ft_calloc(1, new_size)) ;
	new_ptr = ft_calloc(1, new_size);
	if (new_ptr == NULL)
		return (ptr);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	// ft_memmove(new_ptr, ptr, copy_size);
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}
void	single_quote_handling(const char **current, t_token *token)
{
	int value_length;

	value_length = 0;
	if ((*current)[1] == '\0')
	{
		token->type = TOKEN_UNCLOSED_Q;
		token->value = malloc(1); // Allocate memory for null-terminator
		token->value[0] = '\0';
		(*current)++;        
		return ;
	}
	token->type = TOKEN_SINGLE_QUOTE;
	// token->value = malloc(1);
	token->value = NULL;
	(*current)++; 
	while (**current != '\'' && **current != '\0')
	{
		value_length++;
		// token->value = ft_realloc(token->value, ft_strlen(token->value), value_length + 1);
		token->value = ft_realloc(token->value, value_length - 1, value_length + 1);
		token->value[value_length - 1] = **current;
		token->value[value_length] = '\0';
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
	int value_length;

	value_length = 0;
	if ((*current)[1] == '\0')
	{
		token->type = TOKEN_UNCLOSED_Q;
		token->value = malloc(1); // Allocate memory for null-terminator only
		token->value[0] = '\0';
		(*current)++;
		return ;
	}
	token->type = TOKEN_DOUBLE_QUOTE;
	token->value = NULL; // Initialize the value to NULL before reallocating
	(*current)++; // Move past the opening double quote
	while (**current != '"' && **current != '\0')
	{
		value_length++;
		token->value = ft_realloc(token->value, value_length - 1, value_length + 1);
		token->value[value_length - 1] = **current;
		token->value[value_length] = '\0';
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
	// if ((*current)[1] == '\0')
	// {
	// 	token->type = TOKEN_EMPTY;
	// 	token->value = malloc(2); // Allocate memory for null-terminator
	// 	token->value[0] = **current;
	// 	token->value[1] = '\0';
	// 	(*current)++;
	// 	return ;
	// }
	token->type = TOKEN_REDIRECT;
	if ((**current == '<' && *(*current + 1) == '<')
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
// Word token
void	tokenize_word(const char **current, t_token *token)
{
	token->type = TOKEN_WORD;
	int value_length = 0;
	token->value = ft_calloc(1, 1);
	
	while (!(ft_strchr(WHITESPACE, **current)) && !(ft_strchr(OPERAND, **current) && **current != '\0'))
	{
		value_length++;
		token->value = ft_realloc(token->value, ft_strlen(token->value), value_length + 1);
		token->value[value_length - 1] = **current;
		token->value[value_length] = '\0';
		(*current)++;
	}
}

int	strchr_count(const char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}
void	check_assignment(t_token **tokens, int token_count)
{
	int			i;
	int			j;
	const char	*word;

	i = -1;
	while (++i < token_count)
	{
		if ((*tokens)[i].type == TOKEN_WORD || (*tokens)[i].type == TOKEN_SINGLE_QUOTE
			|| (*tokens)[i].type == TOKEN_DOUBLE_QUOTE)
		{
			word = (*tokens)[i].value;
			if (!ft_isalpha(*word) && *word != '_' &&
                ft_strchr(word, '=') && ft_strchr(word, '=') != word)
				continue;
			j = -1;
			while (word[++j] != '=')
			{
				if (!ft_isalnum(word[j]) && word[j] != '_')
					break;
			}
			if (word[j] == '=')
				(*tokens)[i].type = TOKEN_ASSIGNMENT;
		}
	}
}

void tokenize(t_token **tokens, const char *input, int *token_count)
{
	const char  *current;
	t_token     token;

	current = input;
	while (*current != '\0')
	{
		if (*current == '\'')
			single_quote_handling(&current, &token);
		else if (*current == '"')
			double_quote_handling(&current, &token);
		// else if (*current == '|' || *current == '<' || *current == '>')
		else if (ft_strchr(OPERAND, *current))
			tokenize_pipe_and_redirector(&current, &token);
		else if (ft_strchr(WHITESPACE, *current))
		{
			current++;
			continue;
		}
		else
			tokenize_word(&current, &token);
		// Process the token or store it for later processing
		(*token_count)++;
		*tokens = ft_realloc(*tokens, (*token_count - 1) * sizeof(t_token), *token_count * sizeof(t_token));
		(*tokens)[*token_count - 1] = token;
	}
	// (*token_count)++;
	// t_token null_token;
	// null_token.type = TOKEN_END;
	// null_token.value = NULL;
	// null_token.len = *token_count;
	// *tokens = ft_realloc(*tokens, (*token_count - 1) * sizeof(t_token), *token_count * sizeof(t_token));
	// (*tokens)[*token_count - 1] = null_token;
	check_assignment(tokens, *token_count);
}
