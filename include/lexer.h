/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:38:45 by nnavidd           #+#    #+#             */
/*   Updated: 2023/09/11 12:17:15 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "common.h"

t_lexer_state	tokenize(t_minishell *sh, const char *line);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void			print_tokens(t_minishell sh);
void			free_tokens(t_minishell *sh);

#endif
