#include "../include/minishell.h"

const char *token_names[] = {
    "WORD",
    "SIN_QUOTE",
    "DUB_QUOTE",
    "OPERATOR"
    // Add more names for additional token types if needed
};

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
    ft_memmove(new_ptr, ptr, copy_size);
    free(ptr);
    return (new_ptr);
}
void	single_quote(const char **current, t_token *token)
{
    if ((*current)[1] == '\0')
	{
    	(*current)++;
		return ;
	}
	token->type = TOKEN_SINGLE_QUOTE;
    token->value = malloc(1);
    int value_length = 0;
    (*current)++; 
    while (**current != '\'' && **current != '\0')
	{
        value_length++;
        token->value = ft_realloc(token->value, ft_strlen(token->value), value_length + 1);
        token->value[value_length - 1] = **current;
        token->value[value_length] = '\0';
        (*current)++;
    }
    if (**current == '\'')
        (*current)++;
}
void	double_quote(const char **current, t_token *token)
{
    if ((*current)[1] == '\0')
	{
    	(*current)++;
		return ;
	}
	token->type = TOKEN_DOUBLE_QUOTE;
    token->value = malloc(1);
    int value_length = 0;
    (*current)++;
    while (**current != '"' && **current != '\0')
	{
        value_length++;
        token->value = ft_realloc(token->value, ft_strlen(token->value), value_length + 1);
        token->value[value_length - 1] = **current;
        token->value[value_length] = '\0';
        (*current)++;
    }
    if (**current == '"')
        (*current)++;
}
void	pipe_and_redirector(const char **current, t_token *token)
{
    if ((*current)[1] == '\0')
	{
    	(*current)++;
		return ;
	}
	token->type = TOKEN_OPERATOR;
	if (*(*current + 1) == '<' || *(*current + 1) == '>')
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
void	word(const char **current, t_token *token)
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

void tokenize(const char *input)
{
    const char *current = input;
    t_token 	token;
    
    while (*current != '\0')
	{
	    if (*current == '\'')
			single_quote(&current, &token);
        else if (*current == '"')
			double_quote(&current, &token);
        else if (*current == '|' || *current == '<' || *current == '>')
			pipe_and_redirector(&current, &token);
        else if (*current == ' ')
		{
            current++;
            continue;
        }
        else
			word(&current, &token);
        // Process the token or store it for later processing
        
        if (token.value){
	        printf("\033[38;5;04mToken Type\033[0m : \033[38;5;214m%s\033[0m", token_names[token.type]);
			printf("	\033[38;5;196mValue\033[0m : \033[38;5;214m%s\033[0m\n", token.value);

			free(token.value);
			token.value = NULL;
		}
    }
}
