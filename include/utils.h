/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:02:13 by musenov           #+#    #+#             */
/*   Updated: 2023/11/16 15:28:45 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "common.h"
# include "get_next_line.h"

// print_ast.c

void				print_redirect(t_redirect *redirect, int level, char *type);
void				print_assignments(t_assignment *assignment, int level);
void				print_command(char **cmd, int level);
void				print_ast_tree0(t_ast_node *node, int level);
const char			*getAstNodeTypeName(t_ast_node_type type);

// create_ast.c

t_ast_node			*create_ast(void);
t_ast_node			*create_node(void);
void				init_node(t_ast_node *new_node, \
								t_ast_node_type node_type, char **cmd, \
								t_ast_node *new_node_left, \
								t_ast_node *new_node_right);
t_ast_node_content	*create_node_content(void);
void				init_node_content(char **cmd, t_ast_node *new_node);
void				create_node_left(char *cmd_str, t_ast_node **new_node_left);
void				create_node_right(char *cmd_str, \
									t_ast_node **new_node_right);
void				create_node_pipe(t_ast_node **new_node_head, \
						t_ast_node *new_node_left, t_ast_node *new_node_right);

// exit_utils0.c

void				exit_error(int exit_code, char *error_msg, t_pipe *data);
void				exit_zero_exit_code(int exit_code, t_pipe *data);
void				free_all(t_pipe *data);
void				free_str(t_pipe *data);
void				free_2d_str(t_pipe *data);
void				free_2d_str_func(char **str);
void				free_2d_str_cmd_split(t_pipe *data);

// exit_utils1.c

void				exit_error_cmd_notfound(int exit_code, char *error_msg, \
											t_pipe *data);
void				error_do_next_iter(int exit_code, char *error_msg, \
										t_pipe *data);

// free_ast.c

void				free_ast_meder(t_ast_node *node);

#endif
