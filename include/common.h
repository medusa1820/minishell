/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:32:42 by musenov           #+#    #+#             */
/*   Updated: 2023/09/16 16:28:48 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

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

# define BLUE		"\033[38;5;4m"
# define ORG		"\033[38;5;214m"
# define RED		"\033[38;5;196m"
# define RESET		"\033[0m"

# define WHITESPACE	" \t\v\f\r"
# define OPERAND	"<>|\"\'"

/////////////////// common.h

typedef struct s_ast_node	t_ast_node;
typedef struct s_token		t_token;
typedef struct s_lexer		t_lexer;

typedef struct s_minishell
{
	char		*line;
	t_token		*tokens;
	int			token_len;
	int			free_lexer_token_len;
	int			seg_end;
	int			head;
	int			cmd_count;
	int			index;
	int			cmd_index;
	t_ast_node	*ast_root;
}	t_minishell;

/////////////////// lexer.h

typedef enum e_lexer_state
{
	LEXER_SUCCESS,
	UNCLOSED_QUOTE,
	MALLOC_ERROR
}	t_lexer_state;

typedef enum e_token_type
{
	TOKEN_EMPTY,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_REDIRECT,
	TOKEN_PIPE,
	TOKEN_WORD,
	TOKEN_UNCLOSED_Q,
	TOKEN_ASSIGNMENT,
	TOKEN_END,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			flag;
}	t_token;

/////////////////// parser.h

typedef enum e_parser_state
{
	PARSER_SUCCESS,
	PARSER_FAILURE,
	PARSER_SYNTAX_ERROR,
	PARSER_MALLOC_ERROR
}	t_parser_state;

typedef struct s_token		t_token;
typedef struct s_minishell	t_minishell;

typedef enum e_redirect_type
{
	UNDEFINED_TYPE,
	REDIRECT_STDIN,
	REDIRECT_STDOUT,
	REDIRECT_HERE_DOC,
	REDIRECT_STDOUT_APPEND
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

/////////////////// executor.h

typedef struct s_pipe
{
	int				pipe0_fd[2];
	int				pipe1_fd[2];
	pid_t			pid;
	int				nr_of_cmd_nodes;
	char			**paths;
	char			*cmd_path;
	char			**cmd_split;
	int				fd_infile;
	int				fd_outfile;
	bool			here_doc;
	t_minishell		*shell_data;
}	t_pipe;

#endif
