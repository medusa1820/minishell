/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:48:07 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/29 11:57:40 by nnavidd          ###   ########.fr       */
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
// typedef struct s_lexer t_lexer;
typedef struct s_minishell t_minishell;
typedef enum e_redirect_type
{
	REDIRECT_STDIN, //(<)
	REDIRECT_STDOUT, //(>)
	REDIRECT_HERE_DOC, //(<<)
	REDIRECT_STDOUT_APPEND, //(>>)
}	t_redirect_type;

typedef struct s_assignment
{
	char				*word;
	struct s_assignment	*next;
}	t_assignment;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*word;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_ast_node_content
{
	t_redirect		*stdin_redirect;
	t_redirect		*stdout_redirect;
	t_assignment	*assignments;
	char			**cmd;
}	t_ast_node_content;

typedef enum e_ast_node_type
{
	AST_NODE_CMD,
	AST_NODE_PIPE
}	t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	t_ast_node_content	*content;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

void		free_ast(t_ast_node	**node);
void 		print_ast(t_ast_node *root);
// t_ast_node	*parse_pipeline(t_token **tokens, int *token_count);
t_ast_node *parse_pipeline(t_minishell *sh);
void	 	print_ast_node(t_ast_node *node, int level, char x);
bool		init_shell(t_minishell *shell);

#endif
