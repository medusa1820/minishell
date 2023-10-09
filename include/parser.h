/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:48:07 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/09 15:11:24 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "common.h"

// cmd_content_utils.c

t_parser_state	feed_remained_cmd_tokens(t_ast_node_content **content, t_minishell *sh);
size_t			count_strings(char* strings[]);
char			**ft_realloc_strings(char **ptr, size_t old_count, size_t new_count);

// creat_node_content.c

t_parser_state	parse_redirection(t_ast_node_content **content, t_minishell *sh);
t_parser_state	parse_assignment(t_ast_node_content **content, t_minishell *sh);
t_parser_state	parse_cmd_word(t_ast_node_content **content, t_minishell *sh);
t_parser_state	parse_sufix_cmd(t_ast_node_content **content, t_minishell *sh);
t_parser_state	parse_prefix_cmd(t_ast_node_content **content, t_minishell *sh);

// creat_node.c

t_ast_node		*create_command_node(t_ast_node_content *content);
t_ast_node		*create_pipe_node(t_ast_node *left, t_ast_node *right);
t_parser_state	parse_command_content(t_ast_node_content **content, t_minishell *sh);
t_ast_node		*parse_command(t_minishell *sh);
t_ast_node		*parse_pipeline(t_minishell *sh);

// free_ast.c

void			free_content(t_ast_node_content *content);
void			freeing_cmd(char **cmd);
void			freeing_redirection(t_redirect *ptr);
void			freeing_assignment(t_assignment *ptr);
int				free_ast(t_ast_node	*node);

// parsing.c

void			finding_segment_head(t_minishell *sh);
bool			init_shell(t_minishell *shell, t_pipe *data);
t_ast_node		*parsing(t_minishell *sh, char *line);

// print_ast.c

void			print_ast(t_ast_node *root);
void			print_ast_node(t_ast_node *node, int level, char x);

// redirect_content_utils.c

t_redirect_type	redirect_type(char *str);
t_parser_state	add_redirect(t_redirect **redirect, t_redirect *new_redirection);

#endif
