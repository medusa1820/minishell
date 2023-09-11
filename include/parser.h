/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:48:07 by nnavidd           #+#    #+#             */
/*   Updated: 2023/09/11 12:17:20 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "common.h"

int			free_ast(t_ast_node	**node);
void		freeing_assignment(t_assignment *ptr);
void		freeing_redirection(t_redirect *ptr);
void		freeing_cmd(char **cmd);
void		print_ast(t_ast_node *root);
t_ast_node	*parse_pipeline(t_minishell *sh);
void		print_ast_node(t_ast_node *node, int level, char x);
bool		init_shell(t_minishell *shell);

#endif
