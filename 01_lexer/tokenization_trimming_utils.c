/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_trimming_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:36:51 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/09 12:51:23 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((sh->tokens[i].value[0] == '\0') && \
		(sh->tokens[i].type == TOKEN_DOUBLE_QUOTE || \
		sh->tokens[i].type == TOKEN_SINGLE_QUOTE || \
		sh->tokens[i].type == TOKEN_WORD))
		{
			if (!((i - 1 < 0 || sh->tokens[i - 1].type == TOKEN_SPACE)
				&& ((i + 1 >= sh->token_len || \
				sh->tokens[i + 1].type == TOKEN_SPACE))))
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
		if ((sh->tokens[i].type == TOKEN_WORD || sh->tokens[i].type == \
		TOKEN_DOUBLE_QUOTE || sh->tokens[i].type == TOKEN_SINGLE_QUOTE || \
		sh->tokens[i].type == TOKEN_ASSIGNMENT) && (sh->tokens[i + 1].type ==\
		TOKEN_WORD || sh->tokens[i + 1].type == TOKEN_DOUBLE_QUOTE || \
		sh->tokens[i + 1].type == TOKEN_SINGLE_QUOTE))
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
		if (sh->tokens[i].type == TOKEN_PIPE)
			sh->tokens[i].flag = TOKEN_PIPE;
		if (sh->tokens[i].type == TOKEN_SINGLE_QUOTE)
			sh->tokens[i].flag = TOKEN_SINGLE_QUOTE;
		if (sh->tokens[i].type == TOKEN_DOUBLE_QUOTE)
			sh->tokens[i].flag = TOKEN_DOUBLE_QUOTE;
		if (sh->tokens[i].type == TOKEN_REDIRECT)
			sh->tokens[i].flag = TOKEN_REDIRECT;
		if (sh->tokens[i].type == TOKEN_ASSIGNMENT)
			sh->tokens[i].flag = TOKEN_ASSIGNMENT;
		if (sh->tokens[i].type == TOKEN_WORD)
			sh->tokens[i].flag = TOKEN_WORD;
		if ((sh->tokens[i].type == TOKEN_DOUBLE_QUOTE) | \
		(sh->tokens[i].type == TOKEN_SINGLE_QUOTE))
				sh->tokens[i].type = TOKEN_WORD;
	}
}
