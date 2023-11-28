/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:30:44 by musenov           #+#    #+#             */
/*   Updated: 2023/11/27 18:54:03 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_nbr;

/*

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
	{
		return (1);
	}
	return (0);
}

bool	ms_line_is_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

*/

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

int	main(int argc, char **argv)
{
	char		*line;
	t_minishell	shell_data;
	t_pipe		data;
	int			i;
	char		*line_bla;

	(void)argv;//
	if (argc != 1)//
		return (0);//
	init_pipe_data(&data, &shell_data);//
	init_shell(&shell_data, &data);//
	ms_terminal_settings_change();//
	while (1)
	{
		exit_code_signals(&data);
		set_signals_interactive(&data);
		if (isatty(fileno(stdin)))
			line = readline("minishell> ");
		else
		{
			line_bla = get_next_line(fileno(stdin));
			line = ft_strtrim(line_bla, "\n");
			free(line_bla);
		}
		exit_code_signals(&data);
		if (line == NULL || *line == EOF)
		{
			free_envp_ll(shell_data.envp_ll);
			free_envp_local(shell_data.envp_local);
			free_tokens(&shell_data);
			return (data.exit_code);
		}
		if (line[0] != '\0')
		{
			add_history(line);
				set_signals_noninteractive(&data);
				shell_data.ast_root = parsing(&shell_data, line);
				i = 0;
				if (shell_data.ast_root && shell_data.ast_root->type == AST_NODE_CMD)
				{
					piper(&data, &i);
					if (!forker_no_pipe(&data, shell_data.envp_local, shell_data.ast_root))
					{
						free_ast(shell_data.ast_root);
						continue ;
					}
					free_ast(shell_data.ast_root);
					if (data.cmd_splited)
						free_2d_str_cmd_split(&data);
				}
				else
				{
					data.nr_of_cmd_nodes = 0;
					if (!execute_cmds(shell_data.ast_root, &i, &data, shell_data.envp_local))
					{
						free_ast(shell_data.ast_root);
						continue ;
					}
					free_ast(shell_data.ast_root);
				}
			exit_code_signals(&data);
		}
		ft_waiting(&data);
		free(line);
	}
	ms_terminal_settings_restore();
	free_envp_ll(shell_data.envp_ll);
	free_envp_local(shell_data.envp_local);
	return (data.exit_code);
}

