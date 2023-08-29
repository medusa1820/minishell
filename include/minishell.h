/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:32:42 by musenov           #+#    #+#             */
/*   Updated: 2023/08/29 11:28:40 by nnavidd          ###   ########.fr       */
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
# include "parser.h"
# include "lexer.h"

typedef struct s_ast_node t_ast_node;
typedef struct s_token t_token;
typedef struct s_lexer t_lexer;


typedef struct s_minishell
{
	char		*line;
	// t_token 	*tokens;
	t_lexer		*lexer;
	// int			token_len;
	int			free_lexer_token_len;
	int			tmp;
	int			head;
	int			index;
	int			cmd_index;
	t_ast_node *ast_root;
}	t_minishell;

int			main(void);

#endif