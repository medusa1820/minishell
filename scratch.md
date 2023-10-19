========================== COMMANDS TO RUN THE TESTER ======================================






bash ./tester.sh m






mstest m >../msh_test_results/echo_test_0  






diff ../msh_test_results/echo_test_0 ../msh_test_results/test_109 








====================================================================


ls -la | < main.c << E < Makefile  cat >> out_file | grep 1 | wc -c | a=5



====================================================================



set follow-fork-mode child

set follow-fork-mode parent




set follow-exec-mode new

set follow-exec-mode same



====================================================================

                        OPEN PROBLEMS

1. >>, append is not appending LIVE, needs re-opening of out_file

2. 

3. 





====================================================================




first pipe

< in_file0 << E < in_file1 >out_file0 cat >> out_file1 | ls -la







second pipe

ls -la | < in_file0 << E < in_file1 cat >> out_file1 >out_file0

ls -la | < in_file0 << E < in_file1 cat >out_file0 >> out_file1| ls -la

ls -la | < in_file0 cat >> out_file1








third pipe

ls -la | cat > out_file0  | < out_file0 cat >> out_file1

ls -la | grep 3  > out_file0  | < out_file0 cat > out_file1






no pipe

< in_file0 cat > out_file1





========================== TESTING EXIT CODE =====================




bash-3.2$ ls -la | grep 45
bash-3.2$ echo $?
1
bash-3.2$ 







bash-3.2$ ls | cab | cat
bash: cab: command not found
bash-3.2$ echo $?
0
bash-3.2$ 







int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	shell_data;
	int			i;
	t_pipe		data;
	int			status;
	int			exit_code;
	pid_t		wait_pid;

	(void)argc;
	(void)argv;
	(void)envp;
	init_shell(&shell_data);
	data.shell_data = &shell_data;
	// line = readline(RED "minishell> " RESET);
	// if (isatty(fileno(stdin)))
	// 	line = readline("minishell> ");
	// else
	// {
	// 	char *line_bla;
	// 	line_bla = get_next_line(fileno(stdin));
	// 	line = ft_strtrim(line, "\n");
	// 	free(line_bla);
	// }
	while (1)
	{
		if (isatty(fileno(stdin)))
			line = readline("minishell> ");
		else
		{
			char *line_bla;
			line_bla = get_next_line(fileno(stdin));
			line = ft_strtrim(line_bla, "\n"); // line = ft_strtrim(line, "\n");
			free(line_bla);
		}
		if (line == NULL || *line == EOF)
			return (1);
		if (line[0] != '\0')
		{
			add_history(line);
			if (tokenize(&shell_data, line) == LEXER_SUCCESS)
			{
				// print_tokens(shell_data);
				shell_data.ast_root = parse_pipeline(&shell_data);
				if (shell_data.ast_root)
				{
					free_tokens(&shell_data);
					// print_ast_node(shell_data.ast_root, 1, 'x');
					// printf("\n");
					// print_ast_tree0(shell_data.ast_root, 0);
					i = 0;
					// printf("\n");
					if (shell_data.ast_root->type == AST_NODE_CMD)
					{
						piper(&data, &i);
						forker_no_pipe(&data, shell_data.envp_local, shell_data.ast_root);
						free_ast(&shell_data.ast_root);
					}
					else
					{
						data.nr_of_cmd_nodes = 0;
						execute_cmds(shell_data.ast_root, &i, &data, shell_data.envp_local);
						free_ast(&shell_data.ast_root);
						// printf("You entered: %s\n", line);
					}
				}
				else
				{
					printf("PARSER FAILED\n");
					free_tokens(&shell_data);
					free_ast(&shell_data.ast_root);
				}
			}
			else
			{
				printf("LEXER FAILED\n");
				free_tokens(&shell_data);
			}
		}
		wait_pid = 0;
		exit_code = 0;
		while (wait_pid != -1)
		{
			wait_pid = waitpid(-1, &status, 0);
			if (wait_pid == data.pid)
			{
				if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			}
		}
		free(line); // Free the memory allocated by readline
		// print_envp_ll(shell_data.envp_ll);
		// print_envp_local(shell_data.envp_local);
		// line = readline(RED "minishell> " RESET);
	}
	free_envp_ll(shell_data.envp_ll);
	free_envp_local(shell_data.envp_local);
	return (exit_code);
}



// htsang and sawang main()


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
}









int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	shell_data;
	int			i;
	t_pipe		data;
	int			status;
	int			exit_code;
	pid_t		wait_pid;

	(void)argc;
	(void)argv;
	(void)envp;
    init_pipe_data(&data, &shell_data);
	init_shell(&shell_data);
	shell_data.data = &data;
	// init_shell(&shell_data);
	// data.shell_data = &shell_data;
	// line = readline(RED "minishell> " RESET);
	// if (isatty(fileno(stdin)))
	// 	line = readline("minishell> ");
	// else
	// {
	// 	char *line_bla;
	// 	line_bla = get_next_line(fileno(stdin));
	// 	line = ft_strtrim(line, "\n");
	// 	free(line_bla);
	// }
	ms_terminal_settings_change();
	while (1)
	{
		set_signals_interactive();
		if (isatty(fileno(stdin)))
			line = readline("minishell> ");
		else
		{
			char *line_bla;
			line_bla = get_next_line(fileno(stdin));
			line = ft_strtrim(line_bla, "\n"); // line = ft_strtrim(line, "\n");
			free(line_bla);
		}
		set_signals_noninteractive();
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
			if (tokenize(&shell_data, line) == LEXER_SUCCESS)
			{
				// print_tokens(shell_data);
				shell_data.ast_root = parse_pipeline(&shell_data);
				if (shell_data.ast_root)
				{
					free_tokens(&shell_data);
					// print_ast_node(shell_data.ast_root, 1, 'x');
					// printf("\n");
					// print_ast_tree0(shell_data.ast_root, 0);
					i = 0;
					// printf("\n");
					if (shell_data.ast_root->type == AST_NODE_CMD)
					{
						piper(&data, &i);
						forker_no_pipe(&data, shell_data.envp_local, shell_data.ast_root);
						free_ast(&shell_data.ast_root);
					}
					else
					{
						data.nr_of_cmd_nodes = 0;
						execute_cmds(shell_data.ast_root, &i, &data, shell_data.envp_local);
						free_ast(&shell_data.ast_root);
						// printf("You entered: %s\n", line);
					}
				}
				else
				{
					printf("PARSER FAILED\n");
					free_tokens(&shell_data);
					free_ast(&shell_data.ast_root);
				}
			}
			else
			{
				printf("LEXER FAILED\n");
				free_tokens(&shell_data);
			}
		}
		wait_pid = 0;
		// exit_code = 0;
		while (wait_pid != -1)
		{
			wait_pid = waitpid(-1, &status, 0);
			if (wait_pid == data.pid)
			{
				if (WIFEXITED(status))
				data.exit_code = WEXITSTATUS(status);
			}
		}
		free(line); // Free the memory allocated by readline
		// print_envp_ll(shell_data.envp_ll);
		// print_envp_local(shell_data.envp_local);
		// line = readline(RED "minishell> " RESET);
	}
	ms_terminal_settings_restore();
	free_envp_ll(shell_data.envp_ll);
	free_envp_local(shell_data.envp_local);
	return (exit_code);
}
