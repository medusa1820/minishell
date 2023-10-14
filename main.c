/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:30:44 by musenov           #+#    #+#             */
/*   Updated: 2023/10/14 18:35:37 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_nbr;

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
		set_signals_interactive(&data);
		if (isatty(fileno(stdin)))
			line = readline("minishell> ");
		else
		{
			line_bla = get_next_line(fileno(stdin));
			line = ft_strtrim(line_bla, "\n");
			free(line_bla);
		}
		set_signals_noninteractive(&data);
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
			shell_data.ast_root = parsing(&shell_data, line);
			// print_ast_tree0(shell_data.ast_root, 1);
			i = 0;
			if (shell_data.ast_root && shell_data.ast_root->type == AST_NODE_CMD)
			{
				piper(&data, &i);
				forker_no_pipe(&data, shell_data.envp_local, shell_data.ast_root);
				free_ast(shell_data.ast_root);
			}
			else
			{
				data.nr_of_cmd_nodes = 0;
				if(!execute_cmds(shell_data.ast_root, &i, &data, shell_data.envp_local))
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
