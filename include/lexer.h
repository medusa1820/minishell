/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:38:45 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/29 10:31:42 by nnavidd          ###   ########.fr       */
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
# define OPERAND "<>|"


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
    TOKEN_END
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char	*value;
	// bool	check; //check if I didn't use, delete it!
    // int     len;
} t_token;

typedef struct s_lexer
{
	t_token *tokens;
    int     len;
    int     free_len;
}	t_lexer;

typedef struct s_ast_node_content t_ast_node_content;  // Forward declaration
typedef enum e_parser_state t_parser_state;            // Forward declaration


void    tokenize(t_minishell *minishell_data);
void *ft_realloc(void *ptr, size_t old_size, size_t new_size);
// void 	ttokenize(t_token **tokens, const char *input, int *token_count);
void	print_tokens(t_lexer *lexer);
// void	print_tokens(t_token *tokens, int token_count);
void	free_tokens(t_lexer **lexer);
// void	free_tokens(t_token **tokens, int *token_count);

#endif