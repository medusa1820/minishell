/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:39:28 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/09 12:51:28 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	check_assignment(t_token **tokens, int token_count)
{
	int			i;
	int			j;
	const char	*word;

	i = -1;
	while (++i < token_count)
	{
		word = (*tokens)[i].value;
		if (((*tokens)[i].type == TOKEN_WORD || \
			(*tokens)[i].type == TOKEN_SINGLE_QUOTE
			|| (*tokens)[i].type == TOKEN_DOUBLE_QUOTE) && \
			(ft_isalpha(*word) && *word != '_' && *word != '=' && \
			ft_strchr(word, '=') && ft_strchr(word, '=') != word))
		{
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

t_lexer_state	token_unclosed(const char **current, t_token *token)
{
	int	ret;

	ret = UNCLOSED_QUOTE;
	ft_putstr_fd("minishell> ", 2);
	ft_putstr_fd("unexpected EOF while looking for matching ", 2);
	if (token->type == TOKEN_DOUBLE_QUOTE)
		write(2, "`\"\'\n", 4);
	else if (token->type == TOKEN_SINGLE_QUOTE)
		write(2, "`\'\'\n", 4);
	token->type = TOKEN_UNCLOSED_Q;
	(*current)++;
	return (ret);
}

void	back_slash(const char **current, t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*(*current + i) == '\\')
		i++;
	if (!i)
		return ;
	token->slash_number = i;
	if (i % 2 == 0)
		count = i / 2;
	else
		count = (i - 1) / 2;
	i -= count;
	while (i-- && *(*current + 1) != '\0')
			(*current)++;
}

// void	check_assignment(t_token **tokens, int token_count)
// {
// 	int			i;
// 	int			j;
// 	const char	*word;

// 	i = -1;
// 	while (++i < token_count)
// 	{
// 		if ((*tokens)[i].type == TOKEN_WORD || 
// 			(*tokens)[i].type == TOKEN_SINGLE_QUOTE
// 			|| (*tokens)[i].type == TOKEN_DOUBLE_QUOTE)
// 		{
// 			word = (*tokens)[i].value;
// 			if (!ft_isalpha(*word) && *word != '_' && *word != '=' &&
// 				ft_strchr(word, '=') && ft_strchr(word, '=') != word)
// 				continue ;
// 			j = -1;
// 			printf("hiiiiiiii\n");
// 			while (word[++j] != '=')
// 			{
// 				if (!ft_isalnum(word[j]) && word[j] != '_')
// 					break ;
// 			}
// 			if (word[j] == '=' && (*tokens)[i].type != TOKEN_ASSIGNMENT)
// 				(*tokens)[i].type = TOKEN_ASSIGNMENT;
// 		}
// 	}
// }