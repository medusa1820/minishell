/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:32:42 by musenov           #+#    #+#             */
/*   Updated: 2023/07/31 20:59:21 by musenov          ###   ########.fr       */
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

typedef struct s_ast_node
{
	t_ast_node_type		type;
	t_ast_node_content	*content;
	t_ast_node			*left;
	t_ast_node			*right;
}	t_ast_node;

		typedef enum e_ast_node_type
		{
			AST_NODE_CMD,
			AST_NODE_PIPE
		}	t_ast_node_type;

		typedef struct s_ast_node_content
		{
			t_redirect		*stdin_redirect;
			t_redirect		*stdout_redirect;
			t_assignment	*assignments;
			char			**cmd;
		}	t_ast_node_content;

				typedef struct s_redirect
				{
					t_redirect_type	type;
					char			*word;
					t_redirect		*next;
				}	t_redirect;

						typedef enum e_redirect_type
						{
							REDIRECT_STDIN,
							REDIRECT_STDOUT,
							REDIRECT_HERE_DOC,
							REDIRECT_STDOUT_APPEND
						}	t_redirect_type;

				typedef struct s_assignment
				{
					char			*word;
					t_assignment	*next;
				}	t_assignment;


int		main(void);


#endif
