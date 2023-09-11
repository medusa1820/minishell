/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:46:03 by musenov           #+#    #+#             */
/*   Updated: 2023/09/11 20:24:23 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	shell_data;
	int			i;
	t_pipe		data;

	(void)argc;
	(void)argv;
	// (void)envp;
	init_shell(&shell_data);
	line = readline("minishell>");
	while (line)
	{
		if (line[0] != '\0')
		{
			add_history(line);
			if (!tokenize(&shell_data, line))
			{
				// print_tokens(shell_data);
				shell_data.ast_root = parse_pipeline(&shell_data);
				if (shell_data.ast_root)
				{
					free_tokens(&shell_data);
					// print_ast_node(shell_data.ast_root, 1, 'x');
					// printf("\n");
					print_ast_tree0(shell_data.ast_root, 0);
					// printf("\n");
					i = 0;
					data.nr_of_cmd_nodes = 0;
					if (!execute_cmds(shell_data.ast_root, &i, &data, envp))
						free_ast_meder(shell_data.ast_root);
					free_ast(&shell_data.ast_root);
					// printf("You entered: %s\n", line);
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
		// rl_replace_line("", 0); // Clear the current input line 
		// rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		// line = NULL;
		line = readline("minishell> ");
	}
	return (0);
}












/*
==============================================================================
==============================================================================
========================== NAVID FUNCTIONS =================================== 
==============================================================================
==============================================================================
*/








/*

int	main(void)
{
	char		*line;
	t_minishell	shell_data;

	init_shell(&shell_data);
	line = readline("minishell>");
	while (line)
	{
		if (line[0] != '\0')
		{
			add_history(line);
			if (!tokenize(&shell_data, line))
			{
				print_tokens(shell_data);
				shell_data.ast_root = parse_pipeline(&shell_data);
				if (shell_data.ast_root)
				{
					free_tokens(&shell_data);
					print_ast_node(shell_data.ast_root, 1, 'x');
					free_ast(&shell_data.ast_root);
					printf("You entered: %s\n", line); // use the line
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
		rl_replace_line("", 0); // Clear the current input line 
		rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		line = NULL;
		line = readline("minishell> ");
	}
	return (0);
}

*/
















/*
==============================================================================
==============================================================================
========================== MEDER FUNCTIONS =================================== 
==============================================================================
==============================================================================
*/




/*

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			token_count;
	t_ast_node	*ast_root;
	t_token		*tokens;
	t_pipe		data;
	int			i;

	(void)argc;
	(void)argv;
	tokens = NULL;
	ast_root = NULL;
	token_count = 0;
	line = readline("minishell>");
	while (line)
	{
		if (line[0] != '\0')
		{
			add_history(line);
			tokenize(&tokens, line, &token_count);
			print_tokens(tokens, token_count);
			ast_root = parse_pipeline(&tokens, &token_count);
			free_tokens(&tokens, &token_count);
			print_ast_node(ast_root, 1, 'x');
			print_ast_tree0(ast_root, 0);
			printf("\n");
			i = 0;
			data.nr_of_cmd_nodes = 0;
			if (!execute_cmds(ast_root, &i, &data, envp))
				free_ast_meder(ast_root);
			free_ast(&ast_root);
			printf("You entered: %s\n", line); // use the line
		}
		rl_replace_line("", 0); // Clear the current input line 
		rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		line = readline("minishell>");
	}
	return (0);
}

*/







/*

int	main(int argc, char **argv, char **envp)
{
	t_ast_node	*head;
	int			i;
	t_pipe		data;

	(void)argc;
	(void)argv;
	head = create_ast();
	print_ast_tree0(head, 0);
	printf("\n");
	i = 0;
	data.nr_of_cmd_nodes = 0;
	if (!execute_cmds(head, &i, &data, envp))
		free_ast(head);
	free_ast(head);
	return (0);
}


*/






/*

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_ast_node	*head;

	(void)argc;
	(void)argv;
	(void)envp;
	head = NULL;
	line = readline("minishell>");
	while (line)
	{
		add_history(line);
		// printf("You entered: %s\n", line); // use the line
		rl_replace_line("", 0); // Clear the current input line 
		rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		line = readline("minishell>");
	}
	head = create_ast();
	print_ast_tree0(head, 0);
	free_ast_meder(head);
	return (0);
}

*/







/*

ls -la | < main.c << E < Makefile  cat >> out_file | grep 1 | wc -c

ls -la | grep 1 | wc -c | wc -l

*/





