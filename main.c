/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:46:03 by musenov           #+#    #+#             */
/*   Updated: 2023/08/09 17:29:20 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_ast_node create_ast_node(t_ast_node node, char *line)
// {
// 	t_ast_node new_node;

// 	new_node = (t_ast_node) malloc(sizeof(t_ast_node));
//     if (new_node != NULL)
// 	{
//         if ()
// 		new_node.type = SOME_TYPE; // Replace SOME_TYPE with your actual type assignment
//         new_node.content = NULL; // Replace NULL with the appropriate content initialization
//         new_node.left = NULL;
//         new_node.right = NULL;
//     }
//     return new_node;
// }

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
				printf("\033[38;5;04mToken Type\033[0m : \033[38;5;214m%s\033[0m", token_names[tokens[i].type]);
				printf("	\033[38;5;196mValue\033[0m : \033[38;5;214m%s\033[0m\n", tokens[i].value);
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
	char	*line;
	// char	**cmd;
	int		token_count;
	t_token	*tokens;

	tokens = NULL;
	token_count = 0;
	line = readline("minishell>");
	while (line)
	{
		if (line[0] != '\0')
		{
			add_history(line);
			tokenize(&tokens, line, &token_count);
			print_tokens(tokens, token_count);
			free_tokens(&tokens, &token_count);
			printf("You entered: %s\n", line); // use the line
		}
		rl_replace_line("", 0); // Clear the current input line 
		rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		line = readline("minishell>");
	}
	return (0);
}
