/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:15:35 by musenov           #+#    #+#             */
/*   Updated: 2023/10/06 23:22:37 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_minishell		shell_data;
	t_pipe			data;

	(void)argv;
	if (argc != 1)
		return (0);
	init_shell(&shell_data);
	init_pipe_data(&data, &shell_data);
	// ms_terminal_settings_change();
	if (isatty(STDIN_FILENO))
	{
		ms_terminal_settings_change();
		run_minishell_interactive(&data, &shell_data);
		ms_terminal_settings_restore();
	}
	else
		run_minishell_non_interactive(&data, &shell_data);
	free_envp_ll(shell_data.envp_ll);
	free_envp_local(shell_data.envp_local);
	return (data.exit_code);
}

void	run_minishell_interactive(t_pipe *data, t_minishell *shell_data)
{
	char			*line;
	int				i;

	while (1)
	{
		set_signals_interactive();
		line = readline(RED "minishell> " RESET);
		set_signals_noninteractive();
		if (line == NULL || *line == EOF)
		{
			free_envp_ll(shell_data->envp_ll);
			free_envp_local(shell_data->envp_local);
			free_tokens(shell_data);
			// return (data->exit_code);
			return ;
		}
		else if (line[0] != '\0')
		{
			add_history(line);
			if (tokenize(shell_data, line) != LEXER_SUCCESS)
			{
				// printf("LEXER FAILED\n");
				free_tokens(shell_data);
				data->exit_code = 1;
				return ;
			}
			shell_data->ast_root = parse_pipeline(shell_data);
			if (!shell_data->ast_root)
			{
				// printf("PARSER FAILED\n");
				free_tokens(shell_data);
				free_ast(&shell_data->ast_root);
				data->exit_code = 1;
				return ;
			}
			free_tokens(shell_data);
			// print_ast_tree0(shell_data->ast_root, 0);
			i = 0;
			if (shell_data->ast_root->type == AST_NODE_CMD)
			{
				piper(data, &i);
				forker_no_pipe(data, shell_data->envp_local, shell_data->ast_root);
				free_ast(&shell_data->ast_root);
			}
			else
			{
				data->nr_of_cmd_nodes = 0;
				execute_cmds(shell_data->ast_root, &i, data, shell_data->envp_local);
				free_ast(&shell_data->ast_root);
			}
			free(line);
			ft_waiting(data);
		}
		exit_for_signals(data);
	}
}



/*
if (argc >= 2)
	{
		exit_code = ms_non_interactive_mode_from_path(argv[1]);
	}
	else if (isatty(STDIN_FILENO))
	{
		ms_terminal_settings_change();
		ms_signal_handlers_interactive_set();
		exit_code = ms_interactive_mode("minishell$ ");
		ms_terminal_settings_restore();
	}
	else
		exit_code = ms_non_interactive_mode();
*/

void	run_minishell_non_interactive(t_pipe *data, t_minishell *shell_data)
{
	char			*line;
	int				i;
	char			*line_bla;

	while (1)
	{
		set_signals_interactive();
		// char *line_bla;
		line_bla = get_next_line(fileno(stdin));
		line = ft_strtrim(line_bla, "\n"); // line = ft_strtrim(line, "\n");
		free(line_bla);
		set_signals_noninteractive();
		if (line == NULL || *line == EOF)
		{
			free_envp_ll(shell_data->envp_ll);
			free_envp_local(shell_data->envp_local);
			free_tokens(shell_data);
			// return (data->exit_code);
			return ;
		}
		else if (line[0] != '\0')
		{
			add_history(line);
			if (tokenize(shell_data, line) != LEXER_SUCCESS)
			{
				// printf("LEXER FAILED\n");
				free_tokens(shell_data);
				data->exit_code = 1;
				return ;
			}
			shell_data->ast_root = parse_pipeline(shell_data);
			if (!shell_data->ast_root)
			{
				// printf("PARSER FAILED\n");
				free_tokens(shell_data);
				free_ast(&shell_data->ast_root);
				data->exit_code = 1;
				return ;
			}
			free_tokens(shell_data);
			// print_ast_tree0(shell_data->ast_root, 0);
			i = 0;
			if (shell_data->ast_root->type == AST_NODE_CMD)
			{
				piper(data, &i);
				forker_no_pipe(data, shell_data->envp_local, shell_data->ast_root);
				free_ast(&shell_data->ast_root);
			}
			else
			{
				data->nr_of_cmd_nodes = 0;
				execute_cmds(shell_data->ast_root, &i, data, shell_data->envp_local);
				free_ast(&shell_data->ast_root);
			}
			free(line);
			ft_waiting(data);
		}
		exit_for_signals(data);
	}
}

/*
static int	ms_interactive_mode(char *prompt)
{
	struct s_ms		ms;
	t_ms_exit_code	exit_code;

	if (ms_init(&ms))
		return (ms_free(&ms), EXIT_FAILURE);
	ms.line = readline(prompt);
	exit_code = EC_SUCCESS;
	while (ms.line)
	{
		if (ms.line[0] != '\0')
		{
			add_history(ms.line);
			if (!ms_line_is_empty(ms.line))
			{
				ms_signal_handlers_foreground_command_set();
				exit_code = ms_interpret(&ms, ms.line);
				ms_exit_code_save(&ms, exit_code);
				ms_signal_handlers_interactive_set();
			}
		}
		ms_exit_code_save_from_signal(&ms);
		ms_reset(&ms);
		ms.line = readline(prompt);
	}
	return (ms_free(&ms), exit_code);
}
*/

void	run_minishell_interactive1(t_pipe *data, t_minishell *shell_data)
{
	char			*line;
	int				i;

	while (1)
	{
		set_signals_interactive();
		printf("Exit code0: %d\n", data->exit_code);
		line = readline(RED "minishell> " RESET);
		set_signals_noninteractive();
		if (line != NULL)
		{
			if (line[0] != '\0')
			{
				add_history(line);
				if (!tokenize(shell_data, line))
				{
					shell_data->ast_root = parse_pipeline(shell_data);
					if (shell_data->ast_root)
					{
						free_tokens(shell_data);
						print_ast_tree0(shell_data->ast_root, 0);
						i = 0;
						if (shell_data->ast_root->type == AST_NODE_CMD)
						{
							piper(data, &i);
							forker_no_pipe(data, shell_data->envp_local, shell_data->ast_root);
							free_ast(&shell_data->ast_root);
						}
						else
						{
							data->nr_of_cmd_nodes = 0;
							execute_cmds(shell_data->ast_root, &i, data, shell_data->envp_local);
							free_ast(&shell_data->ast_root);
						}
					}
					else
					{
						printf("PARSER FAILED\n");
						free_tokens(shell_data);
						free_ast(&shell_data->ast_root);
					}
				}
				else
				{
					printf("LEXER FAILED\n");
					free_tokens(shell_data);
				}
				free(line);
				ft_waiting(data);
				printf("Exit code1: %d\n", data->exit_code);
			}
		}
		else
		{
			exit_for_signals(data);
			printf("Ctrl + D pressed, exit code is %d", data->exit_code);
			break ;
		}
		exit_for_signals(data);
		printf("Exit code2: %d\n", data->exit_code);
	}
}
