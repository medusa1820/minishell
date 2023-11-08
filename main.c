/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:30:44 by musenov           #+#    #+#             */
/*   Updated: 2023/11/08 18:44:44 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// volatile int	g_sig_nbr;
volatile int	g_sig_nbr;

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

int	main(int argc, char **argv)
{
	char		*line;
	t_minishell	shell_data;
	t_pipe		data;
	int			i;
	char		*line_bla;

	(void)argv;
	if (argc != 1)
		return (0);
	init_pipe_data(&data, &shell_data);
	init_shell(&shell_data, &data);
	ms_terminal_settings_change();
	while (1)
	{
		g_sig_nbr = 0;
		set_signals_interactive(&data);
		if (isatty(fileno(stdin)))
			line = readline(GREEN "minishell> " RESET);
		else
		{
			line_bla = get_next_line(fileno(stdin));
			line = ft_strtrim(line_bla, "\n");
			free(line_bla);
		}
		exit_code_signals(&data);
		if (!ms_line_is_empty(line))
		{
			// ms_signal_handlers_foreground_command_set();
			set_signals_noninteractive(&data);
			exit_code_signals(&data);
			// exit_code = ms_interpret(&ms, ms.line);
			// ms_exit_code_save(&ms, exit_code);
			// ms_signal_handlers_interactive_set();
			set_signals_interactive(&data);
		}
		// set_signals_noninteractive(&data);
		if (line == NULL || *line == EOF)
		{
			free_envp_ll(shell_data.envp_ll);
			free_envp_local(shell_data.envp_local);
			free_tokens(&shell_data);
			return (data.exit_code);
		}
		// exit_code_signals(&data);
		if (line[0] != '\0')
		{
			add_history(line);
			shell_data.ast_root = parsing(&shell_data, line);
			// print_ast_tree0(shell_data.ast_root, 1);
			// print_ast_node(shell_data.ast_root, 1,'X');
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
		}
		ft_waiting(&data);
		free(line);
	}
	ms_terminal_settings_restore();
	free_envp_ll(shell_data.envp_ll);
	free_envp_local(shell_data.envp_local);
	return (data.exit_code);
}
