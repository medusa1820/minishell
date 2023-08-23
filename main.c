/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:46:03 by musenov           #+#    #+#             */
/*   Updated: 2023/08/23 12:19:00 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line;
	int			token_count;
	t_ast_node	*ast_root;
	t_token		*tokens;

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
			free_ast(&ast_root);
			printf("You entered: %s\n", line); // use the line
		}
		rl_replace_line("", 0); // Clear the current input line 
		rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		line = readline("minishell> ");
	}
	return (0);
}
