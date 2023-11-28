/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:34:44 by musenov           #+#    #+#             */
/*   Updated: 2023/11/28 13:59:25 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_nbr;

char	*get_input_line(t_pipe *data)
{
	char		*line_bla;
	char		*line;

	exit_code_signals(data);
	set_signals_interactive(data);
	if (isatty(fileno(stdin)))
		line = readline("minishell> ");
	else
	{
		line_bla = get_next_line(fileno(stdin));
		line = ft_strtrim(line_bla, "\n");
		free(line_bla);
	}
	exit_code_signals(data);
	return (line);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
	{
		return (0);
	}
	return (1);
}

bool	ms_line_has_input(char *line)
{
	while (*line)
	{
		if (ft_isspace(*line))
			return (true);
		line++;
	}
	return (false);
}

int	cleanup_and_exit(t_minishell *shell_data, t_pipe *data)
{
	ms_terminal_settings_restore();
	free_envp_ll(shell_data->envp_ll);
	free_envp_local(shell_data->envp_local);
	return (data->exit_code);
}

void	init_shell_and_pipe(t_minishell *shell_data, t_pipe *data)
{
	init_pipe_data(data, shell_data);
	init_shell(shell_data, data);
}
