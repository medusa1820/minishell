/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:46:03 by musenov           #+#    #+#             */
/*   Updated: 2023/08/03 18:34:06 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_ast_node	*head;
	int			i;
	t_pipe		data;

	head = create_ast();
	print_ast_tree0(head, 0);
	printf("\n");
	i = 0;
	// execute_cmds(head, &i, &data);
	if (!execute_cmds(head, &i, &data))
		free_ast(head);
	free_ast(head);
	return (0);
}

/*

int	main(void)
{
	char		*line;
	t_ast_node	*head;

	head = NULL;
	line = readline("minishell>");
	while (line)
	{
		add_history(line);
		printf("You entered: %s\n", line); // use the line
		rl_replace_line("", 0); // Clear the current input line 
		rl_redisplay(); // Update the display of the input line
		free(line); // Free the memory allocated by readline
		line = readline("minishell>");
	}
	head = create_ast();
	print_ast_tree0(head, 0);
	free_ast(head);
	return (0);
}

*/



/*

ls -la | < main.c << E < Makefile  cat >> out_file | grep 1 | wc -c

ls -la | grep 1 | wc -c | wc -l

*/
