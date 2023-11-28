/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_generation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:34 by nnavidd           #+#    #+#             */
/*   Updated: 2023/11/27 14:50:22 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_token *token)
{
	token->type = TOKEN_EMPTY;
	token->value = NULL;
	token->flag = -1;
	token->slash_number = 0;
}

/* This function feed created tokens to the token list, and each time it 
increases the tokens array memory allocation.*/

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

/* THis function check the received char of tokenize func, and pass them
 to different funcs to create a token of that type.*/

t_lexer_state	checking_tokenizer(t_token *token, t_minishell *sh,
												const char **current)
{
	int			ret;

	ret = LEXER_SUCCESS;
	if (ret == LEXER_SUCCESS && **current == '\'')
		ret = single_quote_handling(current, token);
	else if (ret == LEXER_SUCCESS && **current == '"')
		ret = double_quote_handling(current, token);
	else if (ret == LEXER_SUCCESS && ft_strchr(OPERAND, **current))
		ret = tokenize_pipe_and_redirects(current, token);
	else if (ret == LEXER_SUCCESS && ft_strchr(WHITESPACE, **current))
		ret = tokenize_space(current, token);
	else if (ret == LEXER_SUCCESS)
		ret = tokenize_word(current, token);
	if (ret == LEXER_SUCCESS)
		ret = feed_tokens_array(sh, token);
	return (ret);
}

/* This function pass the line char by char to a checking_tokenizer to create
tokens, and call some functions to work on created token list.*/

t_lexer_state	tokenize(t_minishell *sh, const char *line)
{
	int			ret;
	t_token		token;
	const char	*current;

	ret = LEXER_SUCCESS;
	current = line;
	while (ret == LEXER_SUCCESS && *current != '\0')
	{
		init_token(&token);
		ret = checking_tokenizer(&token, sh, &current);
	}
	sh->free_lexer_token_len = sh->token_len;
	if (ret == LEXER_SUCCESS)
	{
		remove_empty_tokens(sh);
		expander(sh);
		check_assignment(&(sh->tokens), sh->token_len);
		trimming_tokens_type(sh);
		joining_tokens(sh);
		sh->free_lexer_token_len = sh->token_len;
	}
	return (ret);
}

// t_lexer_state	tokenize(t_minishell *sh, const char *line)
// {
// 	int			ret;
// 	t_token		token;
// 	const char	*current;

// 	ret = LEXER_SUCCESS;
// 	current = line;
// 	while (*current != '\0' && ret == LEXER_SUCCESS)
// 	{
// 		init_token(&token);
// 		ret = checking_tokenizer(&token, sh, &current);
// 	}
// 	sh->free_lexer_token_len = sh->token_len;
// 	if (ret == LEXER_SUCCESS)
// 	{
// 		print_tokenss(sh);
// 		printf("before remove empty--------\n");
// 		remove_empty_tokens(sh);
// 		print_tokenss(sh);
// 		printf("before expander--------\n");
// 		expander(sh);
// 		check_assignment(&(sh->tokens), sh->token_len);
// 		print_tokenss(sh);
// 		printf("before triminig--------\n");
// 		trimming_tokens_type(sh);
// 		print_tokenss(sh);
// 		printf("before joining--------\n");
// 		joining_tokens(sh);
// 		sh->free_lexer_token_len = sh->token_len;
// 		print_tokenss(sh);
// 	}
// 	return (ret);
// }
