/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:34 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/05 15:32:50 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_tokens(t_minishell sh)
{
	const char	*token_names[10];
	int			i;

	token_names[0] = "EMPTY";
	token_names[1] = "SIN_QUOTE";
	token_names[2] = "DUB_QUOTE";
	token_names[3] = "REDIRECT";
	token_names[4] = "PIPE";
	token_names[5] = "WORD";
	token_names[6] = "SPACE";
	token_names[7] = "UNCL_QUO";
	token_names[8] = "ASSIGNMNT";
	token_names[9] = "END";
	i = 0;
	while (i < sh.token_len)
	{
		printf(BLUE "Token Type" RESET " : " ORG "%s" RESET, \
		token_names[sh.tokens[i].type]);
		printf(RED "	Value" RESET " : " ORG "%s\n" RESET, \
		sh.tokens[i++].value);
	}
}
void	print_tokenss(t_minishell *sh)
{
	const char	*token_names[10];
	int			i;

	token_names[0] = "EMPTY";
	token_names[1] = "SIN_QUOTE";
	token_names[2] = "DUB_QUOTE";
	token_names[3] = "REDIRECT";
	token_names[4] = "PIPE";
	token_names[5] = "WORD";
	token_names[6] = "SPACE";
	token_names[7] = "UNCL_QUO";
	token_names[8] = "ASSIGNMNT";
	token_names[9] = "END";
	i = 0;
	while (i < sh->token_len)
	{
		printf(BLUE "Token Type" RESET " : " ORG "%s" RESET, \
		token_names[sh->tokens[i].type]);
		printf(RED "	Value" RESET " : " ORG "%s\n" RESET, \
		sh->tokens[i++].value);
	}
}
void	free_tokens(t_minishell *sh)
{
	int	i;

	i = -1;
	while (++i < (*sh).token_len)
		free((*sh).tokens[i].value);
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
	// if (token->value)
	// {
	// 	free(token->value);
	// 	token->value = NULL;
	// }
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
	if ((*current)[1] == '\0')
		return (token_unclosed(current, token));
	token->type = TOKEN_DOUBLE_QUOTE;
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

void	init_token(t_token *token)
{
	token->type = TOKEN_EMPTY;
	token->value = NULL;
	token->flag = false;
}

/*
while characters in token value
	if c == '$' && c + 1 == ('?' || '_' || alpha)
		len = 2
		while (c + len != (alphanumeric || '_'))
			len++;
		var = from first char + len
		get value from var
		if val == NULL -> val is empty
		insert val into var location while keeping everything aroung var (copy before var to new, append val, append rest after var - free old save new)
*/
// $abcde_
int	changing_var_value(char **str, char *value, int start, int len)
{
	char	*new;
	char	*left;
	char	*right;
	int		size;

	left = ft_substr(*str, 0, start);
	right = ft_strdup(*str + start + len);
	if (!left || !right)		
		return (free(left), free(right), start + len - 1);
	if (!value)
		value = "";
	size = ft_strlen(left) + ft_strlen(right) + ft_strlen(value) + 1;
	new = ft_calloc(size, sizeof(char));
	if (!new)
		return (free(left), free(right), start + len - 1);
	ft_strlcpy(new, left, size);
	ft_strlcat(new, value, size);
	ft_strlcat(new, right, size);
	free(*str);
	*str = new;
	return (free(left), free(right), start + ft_strlen(value) - 1);
}
char	*get_env_var(t_minishell *sh, char *var)
{
	t_envp_ll	*tmp;

	if (var == NULL)
		return (NULL);
	tmp = sh->envp_ll;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, var, ft_strlen(tmp->var)))
				return (ft_strdup(tmp->value)); 
		tmp = tmp->next;
	}
	return (NULL);
}

void expand(t_minishell *sh, char **str, int j)
{
	int		i;
	char	*var;
	char	*value;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			value = NULL;
			j = i + 2;
			if ((*str)[i + 1] == '?')
				value = ft_itoa(sh->data->exit_code);// put the the correct exit code here
			else if ((*str)[i + 1] == '_' || ft_isalpha((*str)[i + 1]))
			{
				while ((*str)[j] == '_' || ft_isalnum((*str)[j]))
					j++;
				var = ft_substr(*str, i + 1, j - i);
				value = get_env_var(sh, var);
				free(var);
			}
			i = changing_var_value(str, value, i, j - i);
			free(value);
		}
	}
}

void	expandor(t_minishell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < sh->token_len)
	{
		if ((sh->tokens[i].type == TOKEN_DOUBLE_QUOTE) || (sh->tokens[i].type == TOKEN_WORD))
			expand(sh, &sh->tokens[i].value, j);
		i++;
	}
}


//ls -la |  < main.c << E < make cat >> out | $USER
	

void erase_token(t_minishell *sh, int index)
{
	int	i;

	i = index;
	if (index < 0 || index >= sh->token_len)
		return;
	free(sh->tokens[index].value);
	sh->tokens[index].value = NULL;
	while (i < sh->token_len - 1)
	{
		sh->tokens[i] = sh->tokens[i + 1];
		i++;
	}
	sh->token_len--;
}

// 	for each token
// 	if WORD is empty
// 		check left and right token
// 		if both are space or either one is out of bounds
// 			leave empty word
// 		else
// 			remove empty WORD
// remove all space tokens
void	remove_empty_tokens(t_minishell *sh)
{
	int	i;

	i = -1;
	while (++i < sh->token_len)
	{
		if ((sh->tokens[i].value[0] == '\0') && (sh->tokens[i].type == TOKEN_DOUBLE_QUOTE || sh->tokens[i].type == TOKEN_SINGLE_QUOTE || sh->tokens[i].type == TOKEN_WORD))
		{
			if (!((i - 1 < 0 || sh->tokens[i - 1].type == TOKEN_SPACE)
				&& ((i + 1 >= sh->token_len || sh->tokens[i + 1].type == TOKEN_SPACE))))
				erase_token(sh, i);
		}
	}
}
void	joining_tokens(t_minishell *sh)
{
	int		i;
	char	*tmp_token;

	i = 0;
	while (i < sh->token_len - 1)
	{
		if ((sh->tokens[i].type == TOKEN_WORD || sh->tokens[i].type == TOKEN_DOUBLE_QUOTE || sh->tokens[i].type == TOKEN_SINGLE_QUOTE) && (sh->tokens[i + 1].type == TOKEN_WORD || sh->tokens[i + 1].type == TOKEN_DOUBLE_QUOTE || sh->tokens[i + 1].type == TOKEN_SINGLE_QUOTE))
		{
			tmp_token = ft_strjoin(sh->tokens[i].value, sh->tokens[i + 1].value);
			free(sh->tokens[i].value);
			sh->tokens[i].value = tmp_token;
			erase_token(sh, i + 1);
		}
		else 
			i++;
	}	
	i = -1;
	while (++i < sh->token_len)
	{
		if (sh->tokens[i].type == TOKEN_SPACE)
			erase_token(sh, i);
	}
}
void	trimming_tokens_type(t_minishell *sh)
{
	int	i;

	i = -1;
	while (++i < sh->token_len)
	{
		if ((sh->tokens[i].type == TOKEN_DOUBLE_QUOTE) | \
		(sh->tokens[i].type == TOKEN_SINGLE_QUOTE))
				sh->tokens[i].type = TOKEN_WORD;
	}
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
		// print_tokenss(sh);
		check_assignment(&(sh->tokens), sh->token_len);
		remove_empty_tokens(sh);
		expandor(sh);
		trimming_tokens_type(sh);
		joining_tokens(sh);
	}
	return (ret);
}
