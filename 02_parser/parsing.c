/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:39:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/14 18:38:24 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printing_syntax_error(char *syntax, int syx_pos, char *nx_syx, t_minishell *sh, int fd)
{
	if (syntax && ft_strcmp(syntax, "<<\0") && ft_strcmp(nx_syx, "<<\0"))
	{
		if (syx_pos + 2 < sh->seg_end && \
		ft_strcmp(sh->tokens[syx_pos + 2].value, "<<\0"))
			ft_putstr_fd(syntax, fd);
		if (syx_pos + 2 < sh->seg_end && \
		ft_strcmp(sh->tokens[syx_pos + 2].value, "<\0"))
			write(fd, "<", 1);
		write(fd, "<'\n", 3);
		return ;
	}
	if ((syx_pos >= 0 && syx_pos <= sh->seg_end) && nx_syx)
	{
		if ((ft_strcmp(syntax, "<\0") && ft_strcmp(nx_syx, ">\0")) || \
		(ft_strcmp(syntax, "<<\0") && ft_strcmp(nx_syx, "<\0")))
			ft_putstr_fd("newline", fd);
		else
			ft_putstr_fd(nx_syx, fd);
	}
	else if (syntax && syx_pos < 0 && \
	syx_pos < sh->seg_end && !ft_strcmp(nx_syx, "|\0"))
		ft_putstr_fd(syntax, fd);
	else if ((syx_pos >= 0 && syx_pos < sh->seg_end) && \
	!nx_syx && syx_pos + 1 == sh->free_lexer_token_len)
		ft_putstr_fd("newline", fd);
	else
		ft_putstr_fd("|", 2);
	write(fd, "'\n", 2);
}

void	find_syntax_error(t_minishell *sh, int fd)
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
	printing_syntax_error(syntax, syntax_position, next_token, sh, fd);
}

void	print_error2(char *type, int fd, char *msg, t_minishell *sh)
{
	ft_putstr_fd("minishell: ", fd);
	if (type)
	{
		ft_putstr_fd(type, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
	find_syntax_error(sh, fd);
}

void	print_error(char *type, int fd, char *msg)
{
	ft_putstr_fd("minishell: ", fd);
	if (type)
	{
		ft_putstr_fd(type, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
}

void	finding_segment_head(t_minishell *sh)
{
	sh->head = sh->token_len - 1;
	sh->seg_end = sh->token_len;
	while (sh->head >= 0)
	{
		if (sh->tokens[sh->head].type == TOKEN_PIPE)
			break ;
		if ((sh->head - 1) >= 0 && sh->tokens[sh->head - 1].type == TOKEN_PIPE)
			break ;
		sh->head--;
	}
	if (sh->head < 0)
		sh->head = 0;
}

bool	init_shell(t_minishell *shell, t_pipe *data)
{
	shell->ast_root = NULL;
	shell->tokens = NULL;
	shell->token_len = 0;
	shell->free_lexer_token_len = 0;
	shell->seg_end = 0;
	shell->head = 0;
	shell->cmd_count = 0;
	shell->index = 0;
	shell->cmd_index = 0;
	shell->space_flag = false;
	shell->line = NULL;
	shell->data = data;
	init_envp_linked_list(shell);
	envp_ll_to_envp_local(shell);
	return (true);
}

t_ast_node	*parsing(t_minishell *sh, char *line)
{
	if (tokenize(sh, line) == LEXER_SUCCESS)
	{
		if (!sh->token_len)
			return (NULL);
		sh->ast_root = parse_pipeline(sh);
		if (!sh->ast_root)
		{
			free_tokens(sh);
			free_ast(sh->ast_root);
			return (NULL);
		}
		free_tokens(sh);
		return (sh->ast_root);
	}
	else
	{
		printf("hi\n");
		sh->data->exit_code = 2;
		free_tokens(sh);
	}
	return (NULL);
}
