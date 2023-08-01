/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:46:03 by musenov           #+#    #+#             */
/*   Updated: 2023/08/01 13:58:04 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	create_ast();
	return (0);
}





/*

ls -la | < main.c << E < Makefile  cat >> out_file | grep 1 | wc -c

ls -la | grep 1 | wc -c

*/

void	create_ast(t_ast_node *head)
{
	
}


t_ast_node	*create_node(void)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	new_node->content = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}


void	add_node(t_ast_node *head)
{
	t_ast_node	*new_node;
	t_ast_node	*current;

	new_node = create_node();
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	new_node->prev = current;
}

void	add_node(t_node **head, int num)
{
	t_node	*new_node;
	t_node	*current;

	new_node = create_node(num);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	new_node->prev = current;
}

int	count_nodes(t_node *stack)
{
	t_node	*node;
	int		count;

	node = stack;
	count = 0;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}

t_node	*find_last_node(t_node *head)
{
	t_node	*current;

	current = head;
	while (current != NULL && current->next != NULL)
		current = current->next;
	return (current);
}
