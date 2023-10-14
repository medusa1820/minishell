/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:39:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/10 13:58:43 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *type, int fd, char *msg)
{
	ft_putstr_fd("minishell: ", fd);
	if(type)
	{
		ft_putstr_fd(type, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
	// perror(msg);
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
		sh->ast_root = parse_pipeline(sh);
		if (!sh->ast_root)
		{
			// printf("PARSER FAILED\n");
			free_tokens(sh);
			free_ast(sh->ast_root);
			return (NULL);
		}
		return (sh->ast_root);
	}
	else
	{
		printf("LEXER FAILED\n");
		free_tokens(sh);
	}
	return (NULL);
}
