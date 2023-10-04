#include "minishell.h"

extern char	**environ;

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
