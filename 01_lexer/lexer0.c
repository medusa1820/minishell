#include "../include/minishell.h"



void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

 	if (new_size == 0)
	{
		free(ptr);
		return NULL;
	}
	if (ptr == NULL)
		return (malloc(new_size)) ;
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (ptr);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	// ft_memmove(new_ptr, ptr, copy_size);
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
void	single_quote_handling(const char **current, t_token *token)
{
	int value_length;

	value_length = 0;
	if ((*current)[1] == '\0')
	{
		token->type = TOKEN_EMPTY;
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
}
void double_quote_handling(const char **current, t_token *token)
{
    int value_length;

	value_length = 0;
    if ((*current)[1] == '\0')
    {
        token->type = TOKEN_EMPTY;
        token->value = malloc(1); // Allocate memory for null-terminator only
        token->value[0] = '\0';
        (*current)++;
        return;
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
	token->type = TOKEN_OPERATOR;
	if ((**current == '<' || **current == '>') 
		&& (*(*current + 1) == '<' || *(*current + 1) == '>'))
	{
		token->value = malloc(3);
		token->value[0] = **current;
		(*current)++;
		token->value[1] = **current;
		token->value[2] = '\0';
	}
	else
	{
		token->value = malloc(2);
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
	token->value = malloc(1);
	
	while (**current != ' ' && **current != '\0')
	{
		value_length++;
		token->value = ft_realloc(token->value, ft_strlen(token->value), value_length + 1);
		token->value[value_length - 1] = **current;
		token->value[value_length] = '\0';
		(*current)++;
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
		else if (*current == '|' || *current == '<' || *current == '>')
			tokenize_pipe_and_redirector(&current, &token);
		else if (*current == ' ')
		{
			current++;
			continue;
		}
		else
			tokenize_word(&current, &token);
		// Process the token or store it for later processing
		(*token_count)++;
		*tokens = ft_realloc(*tokens, *token_count - 1 * sizeof(t_token), *token_count * sizeof(t_token));
		(*tokens)[*token_count - 1] = token;
		// free(token.value);
		// token.value = NULL;
	}
}
