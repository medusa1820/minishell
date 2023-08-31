/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:46:03 by musenov           #+#    #+#             */
/*   Updated: 2023/08/31 17:08:34 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"

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
				free_tokens(&shell_data);
				print_ast_node(shell_data.ast_root, 1, 'x');
				free_ast(&shell_data.ast_root);
				printf("You entered: %s\n", line); // use the line
			}
			printf("Unclosed quotation\n");
			free_tokens(&shell_data);
		}
		rl_replace_line("", 0); // Clear the current input line 
		rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		line = NULL;
		line = readline("minishell> ");
	}
	return (0);
}
