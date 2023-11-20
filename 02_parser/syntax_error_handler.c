/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:33:19 by nnavidd           #+#    #+#             */
/*   Updated: 2023/11/20 14:27:43 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_state	check_and_set_syntax_error_flag(t_minishell *sh, int ret)
{
	if (ret)
	{
		if (sh->head >= 0 && sh->head < sh->seg_end && \
			sh->tokens[sh->head].flag && \
			sh->tokens[sh->head].flag != TOKEN_WORD)
			sh->tokens[sh->head].flag = -2;
	}
	return (ret);
}

void	unexpected_token_heredoc(char *syntax, int syx_pos, t_minishell *sh)
{
	if (syx_pos + 2 < sh->seg_end && \
	ft_strcmp(sh->tokens[syx_pos + 2].value, "<<\0"))
		ft_putstr_fd(syntax, 2);
	if (syx_pos + 2 < sh->seg_end && \
	ft_strcmp(sh->tokens[syx_pos + 2].value, "<\0"))
		write(2, "<", 1);
	write(2, "<'\n", 3);
	return ;
}

void	printing_syntax_error(char *syntax, int syx_pos, char *nx_syx, \
															t_minishell	*sh)
{
	if (syntax && ft_strcmp(syntax, "<<\0") && ft_strcmp(nx_syx, "<<\0"))
	{
		return (unexpected_token_heredoc(syntax, syx_pos, sh));
	}
	if ((syx_pos >= 0 && syx_pos <= sh->seg_end) && nx_syx)
	{
		if ((ft_strcmp(syntax, "<\0") && ft_strcmp(nx_syx, ">\0")) || \
		(ft_strcmp(syntax, "<<\0") && ft_strcmp(nx_syx, "<\0")))
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(nx_syx, 2);
	}
	else if (syntax && syx_pos < 0 && \
	syx_pos < sh->seg_end && !ft_strcmp(nx_syx, "|\0"))
		ft_putstr_fd(syntax, 2);
	else if ((syx_pos >= 0 && syx_pos < sh->seg_end) && \
	!nx_syx && syx_pos + 1 == sh->free_lexer_token_len)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd("|", 2);
	write(2, "'\n", 2);
}

void	finding_syntax_error_flag(t_minishell *sh)
{
	int		i;
	char	*syntax;
	char	*next_token;
	int		syntax_position;

	i = -1;
	next_token = NULL;
	syntax = NULL;
	syntax_position = -1;
	while (++i < sh->seg_end)
	{
		if (sh->tokens[i].flag == -2)
			syntax_position = i;
	}
	if (syntax_position >= 0)
	{
		syntax = sh->tokens[syntax_position].value;
		if (syntax_position + 1 < sh->seg_end)
			next_token = sh->tokens[syntax_position + 1].value;
	}
	printing_syntax_error(syntax, syntax_position, next_token, sh);
}
