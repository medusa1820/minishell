/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:46:03 by musenov           #+#    #+#             */
/*   Updated: 2023/08/16 15:33:41 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *token_names[] = {
	"WORD",
	"SIN_QUOTE",
	"DUB_QUOTE",
	"REDIRECT",
	"PIPE",
	"EMPTY",
	"UNCL_QUO",
	"ASSIGNMNT"
	// Add more names for additional token types if needed
};

void	print_tokens(t_token *tokens, int token_count)
{
		for(int i = 0; i < token_count; i++)
		{
				printf(BLUE "Token Type" RESET " : " ORG "%s" RESET, token_names[tokens[i].type]);
				printf(RED "	Value" RESET " : " ORG "%s\n" RESET, tokens[i].value);
		}

}

void	free_tokens(t_token **tokens, int *token_count)
{
	int	i;

	i = -1;
	while (++i < *token_count)
	{
		if((*tokens)[i].value)
		{
			free((*tokens)[i].value);
			(*tokens)[i].value = NULL;
		}
	}
	free(*tokens);
	*tokens = NULL;
	*token_count = 0;
}

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
			print_ast_tree0(ast_root, 0);
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
