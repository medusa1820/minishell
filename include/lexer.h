/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:38:45 by nnavidd           #+#    #+#             */
/*   Updated: 2023/11/27 14:50:22 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "common.h"

// free_print_tokens.c

void			print_tokens(t_minishell sh);
void			print_tokenss(t_minishell *sh);
void			free_tokens(t_minishell *sh);

// lexer_generation.c

void			init_token(t_token *token);
t_lexer_state	feed_tokens_array(t_minishell *sh, t_token *token);
t_lexer_state	checking_tokenizer(t_token *token, t_minishell *sh, \
													const	char **current);
t_lexer_state	tokenize(t_minishell *sh, const char *line);

// tokenization_trimming_utils.c

void			erase_token(t_minishell *sh, int index);
void			remove_empty_tokens(t_minishell *sh);
void			joining_tokens(t_minishell *sh);
void			trimming_tokens_type(t_minishell *sh);

// tokenization_utils.c

void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void			check_assignment(t_token **tokens, int token_count);
t_lexer_state	token_unclosed(const char **current, t_token *token);
void			back_slash(const char **current, t_token *token);

// tokens_type.c

t_lexer_state	single_quote_handling(const char **current, t_token *token);
t_lexer_state	double_quote_handling(const char **current, t_token *token);
t_lexer_state	tokenize_pipe_and_redirects(const char **current, \
															t_token *token);
t_lexer_state	tokenize_space(const char **current, t_token *token);
t_lexer_state	tokenize_word(const char **current, t_token *token);

#endif
