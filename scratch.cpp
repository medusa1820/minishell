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
			line = readline(GREEN "minishell> " RESET);
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






//////////////////////////////////////////////////////






static int	ms_non_interactive_mode(void)
{
	struct s_ms				ms;
	t_ms_exit_code			exit_code;
	int						iostream_read_status;

	if (ms_init(&ms))
		return (ms_free(&ms), EXIT_FAILURE);
	exit_code = EC_SUCCESS;
	iostream_read_status = EXIT_SUCCESS;
	while (iostream_read_status == EXIT_SUCCESS)
	{
		iostream_read_status = ft_iostream_read_until_delimiter(\
			&ms.executor.stdin_stream, STDIN_FILENO, \
			(t_ft_str){"\n", 1});
		ms.line = ft_str_to_cstring(ft_iostream_to_slice(\
			&ms.executor.stdin_stream));
		if ((ms.line != NULL) && !ms_line_is_empty(ms.line))
		{
			exit_code = ms_interpret(&ms, ms.line);
			ms_exit_code_save(&ms, exit_code);
		}
		ms_reset(&ms);
	}
	ms_free(&ms);
	return (exit_code);
}

static int	ms_non_interactive_mode_from_path(const char *path)
{
	t_ms_exit_code	exit_code;
	int				fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ms_exit_code_evaluate(path, true, true));
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		exit_code = ms_non_interactive_mode();
	}
	return (exit_code);
}

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

int	main(int argc, char **argv)
{
	t_ms_exit_code	exit_code;

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
	return (exit_code);
	// (void)argc;
	// (void)argv;
	// if (isatty(STDIN_FILENO))
	// {
	// 	ms_terminal_settings_change();
	// 	ms_signal_handlers_interactive_set();
	// 	exit_code = ms_interactive_mode("minishell$ ");
	// 	ms_terminal_settings_restore();
	// }
	// else
	// 	exit_code = ms_non_interactive_mode();
	// return (exit_code);
}
