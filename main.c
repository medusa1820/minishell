/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:46:03 by musenov           #+#    #+#             */
/*   Updated: 2023/08/29 13:28:16 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line;
	// int			token_count;
	// t_ast_node	*ast_root;
	// t_token		*tokens;
	t_minishell	shell_data;

	// sh = NULL;
	init_shell(&shell_data);
	// ast_root = shell_data.ast_root;
	line = readline("minishell>");
	while (line)
	{
		if (line[0] != '\0')
		{
			add_history(line);
			// tokenize(&shell_data.tokens, line, &shell_data.token_len);
			tokenize(&shell_data, line);
			// print_tokens(tokens, token_count);
			print_tokens(shell_data);
	
			// tokens = shell_data.tokens;
			// token_count = shell_data.token_len;
			// ast_root = parse_pipeline(&tokens, &token_count);
			shell_data.ast_root = parse_pipeline(&shell_data);

			free_tokens(&shell_data);
			
			print_ast_node(shell_data.ast_root, 1, 'x');
			free_ast(&shell_data.ast_root);
			printf("You entered: %s\n", line); // use the line
		}
		rl_replace_line("", 0); // Clear the current input line 
		rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		line = NULL;
		line = readline("minishell> ");
	}
	return (0);
}
