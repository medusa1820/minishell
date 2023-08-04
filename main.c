/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:46:03 by musenov           #+#    #+#             */
/*   Updated: 2023/08/04 13:15:56 by nnavidd          ###   ########.fr       */
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


int	main(void)
{
	char	*line;
	// char	**cmd;

	line = readline("minishell>");
	while (line)
	{
		add_history(line);
		// if (!ft_strchr(line, '|'))
		// {
		// 	free(line);
		// 	return (0);
		// }
		// cmd = split_string(line);
		// print_cmd(cmd);
		tokenize(line);
		printf("You entered: %s\n", line); // use the line
		rl_replace_line("", 0); // Clear the current input line 
		rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		line = readline("minishell>");
	}
	return (0);
}
