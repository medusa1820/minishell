/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:48:07 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/25 18:33:43 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lib/ft_printf/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"


typedef enum e_parser_state
{
	PARSER_SUCCESS,
	PARSER_FAILURE,
	PARSER_SYNTAX_ERROR,
	PARSER_MALLOC_ERROR
}	t_parser_state;

typedef struct s_token t_token;
typedef struct s_ast_node t_ast_node;

// typedef struct s_minishell
// {
// 	char		*line;
// 	t_token 	*tokens;
// 	int			token_len;
// 	t_ast_node *ast_root;
// }	t_minishell;

void		free_ast(t_ast_node	**node);
void 		print_ast(t_ast_node *root);
t_ast_node	*parse_pipeline(t_token **tokens, int *token_count);
void	 	print_ast_node(t_ast_node *node, int level, char x);

#endif
