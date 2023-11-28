/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:34:44 by musenov           #+#    #+#             */
/*   Updated: 2023/11/28 18:50:41 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_nbr;

int	process_line(t_minishell *shell_data, t_pipe *data, char *line)
{
	int	i;

	add_history(line);
	set_signals_noninteractive(data);
	shell_data->ast_root = parsing(shell_data, line);
	i = 0;
	if (shell_data->ast_root && shell_data->ast_root->type == AST_NODE_CMD)
	{
		if (process_cmd(shell_data, data, &i))
			return (1);
	}
	else
	{
		if (process_non_cmd(shell_data, data, &i))
			return (1);
	}
	exit_code_signals(data);
	return (0);
}

int	process_non_cmd(t_minishell *shell_data, t_pipe *data, int *i)
{
	data->nr_of_cmd_nodes = 0;
	if (!execute_cmds(shell_data->ast_root, i, data, shell_data->envp_local))
	{
		free_ast(shell_data->ast_root);
		return (1);
	}
	free_ast(shell_data->ast_root);
	return (0);
}

int	process_cmd(t_minishell *shell_data, t_pipe *data, int *i)
{
	piper(data, i);
	if (!forker_no_pipe(data, shell_data->envp_local, shell_data->ast_root))
	{
		free_ast(shell_data->ast_root);
		return (1);
	}
	free_ast(shell_data->ast_root);
	if (data->cmd_splited)
		free_2d_str_cmd_split(data);
	return (0);
}

void	process_input(t_minishell *shell_data, t_pipe *data)
{
	char	*line;

	while (1)
	{
		line = get_input_line(data);
		if (!line || *line == EOF)
		{
			free_envp_ll(shell_data->envp_ll);
			free_envp_local(shell_data->envp_local);
			free_tokens(shell_data);
			exit (data->exit_code);
			break ;
		}
		else if (*line != '\0')
			if (process_line(shell_data, data, line))
				continue ;
		ft_waiting(data);
		free(line);
	}
}

int	main(int argc, char **argv)
{
	t_minishell	shell_data;
	t_pipe		data;

	(void)argv;
	if (argc != 1)
		return (0);
	init_shell_and_pipe(&shell_data, &data);
	ms_terminal_settings_change();
	process_input(&shell_data, &data);
	ms_terminal_settings_restore();
	return (cleanup_and_exit(&shell_data, &data));
}
