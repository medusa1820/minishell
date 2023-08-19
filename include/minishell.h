/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:32:42 by musenov           #+#    #+#             */
/*   Updated: 2023/08/19 16:11:46 by nnavidd          ###   ########.fr       */
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
	// t_redirect		*stdin_redirect;
	// t_redirect		*stdout_redirect;
	t_redirect		*redirection;
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
// char		**split_string(char *input_string);
// void		print_cmd(char **cmd);
#endif