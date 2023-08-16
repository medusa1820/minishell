/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:32:42 by musenov           #+#    #+#             */
/*   Updated: 2023/08/16 11:09:08 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
// # include "get_next_line.h"

#define BLUE  "\033[38;5;4m"
#define ORG   "\033[38;5;214m"
#define RED   "\033[38;5;196m"
#define RESET "\033[0m"

# define WHITESPACE " \t\v\f\r"
# define OPERAND "<>|"
typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_SINGLE_QUOTE,
    TOKEN_DOUBLE_QUOTE,
    TOKEN_REDIRECT,
	TOKEN_PIPE,
	TOKEN_EMPTY,
	TOKEN_UNCLOSED_Q,
	TOKEN_ASSIGNMENT
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char	*value;
	bool	check; //check if I didn't use, delete it!
} t_token;

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

int			main(void);
char		**split_string(char *input_string);
void		print_cmd(char **cmd);
void 		tokenize(t_token **tokens, const char *input, int *token_count);
void 		free_ast(t_ast_node **node);
void 		print_ast(t_ast_node *root);
t_ast_node	*parse_pipeline(t_token **tokens, int *token_count);
void	 	print_ast_node(t_ast_node *node, int level, char x);
#endif