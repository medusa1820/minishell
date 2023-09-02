/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:38:45 by nnavidd           #+#    #+#             */
/*   Updated: 2023/09/01 11:58:42 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define BLUE  "\033[38;5;4m"
# define ORG   "\033[38;5;214m"
# define RED   "\033[38;5;196m"
# define RESET "\033[0m"

# define WHITESPACE " \t\v\f\r"
# define OPERAND "<>|\"\'"

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

typedef struct s_ast_node_content	t_ast_node_content;
typedef enum e_parser_state	t_parser_state;

t_lexer_state	tokenize(t_minishell *sh, const char *line);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	print_tokens(t_minishell sh);
void	free_tokens(t_minishell *sh);

#endif