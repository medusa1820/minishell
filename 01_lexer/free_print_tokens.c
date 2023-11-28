/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_print_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:40:42 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/09 11:09:13 by nnavidd          ###   ########.fr       */
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
	while (++i < (*sh).free_lexer_token_len)
	{
		free((*sh).tokens[i].value);
		(*sh).tokens[i].value = NULL;
	}
	free((*sh).tokens);
	(*sh).tokens = NULL;
	(*sh).token_len = 0;
	(*sh).free_lexer_token_len = 0;
}
