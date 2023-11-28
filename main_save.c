/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:30:44 by musenov           #+#    #+#             */
/*   Updated: 2023/11/28 10:06:59 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_nbr;

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



// void	init_shell_and_pipe(t_minishell *shell_data, t_pipe *data)
// {
// 	init_pipe_data(data, shell_data);
// 	init_shell(shell_data, data);
// }

void	process_cmd(t_minishell *shell_data, t_pipe *data, int *i)
{
	piper(data, i);
	if (!forker_no_pipe(data, shell_data->envp_local, shell_data->ast_root))
	{
		free_ast(shell_data->ast_root);
		return ;
	}
	free_ast(shell_data->ast_root);
	if (data->cmd_splited)
		free_2d_str_cmd_split(data);
}


void	process_non_cmd(t_minishell *shell_data, t_pipe *data, int *i) {
	data->nr_of_cmd_nodes = 0;

	if (!execute_cmds(shell_data->ast_root, i, data, shell_data->envp_local))
	{
		free_ast(shell_data->ast_root);
		return ;
	}

	free_ast(shell_data->ast_root);
}

void	process_line(t_minishell *shell_data, t_pipe *data, char *line)
{
	int	i;

	add_history(line);
	set_signals_noninteractive(data);
	shell_data->ast_root = parsing(shell_data, line);
	i = 0;

	if (shell_data->ast_root && shell_data->ast_root->type == AST_NODE_CMD)
		process_cmd(shell_data, data, &i);
	else
		process_non_cmd(shell_data, data, &i);
	exit_code_signals(data);
}

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

void	process_input(t_minishell *shell_data, t_pipe *data)
{
	char	*line;

	while (1)
	{
		line = get_input_line(data);
		if (!line || *line == EOF || *line == '\0')
		{
			free_tokens(shell_data);
			break ;
		}
		else
			process_line(shell_data, data, line);
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

	// init_shell_and_pipe(&shell_data, &data);
	init_pipe_data(&data, &shell_data);
	init_shell(&shell_data, &data);

	ms_terminal_settings_change();
	process_input(&shell_data, &data);
	ms_terminal_settings_restore();

	return (cleanup_and_exit(&shell_data, &data));
}
