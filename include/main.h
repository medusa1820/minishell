/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:48:32 by musenov           #+#    #+#             */
/*   Updated: 2023/08/06 14:03:12 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// main.c

int					main(int argc, char **argv, char **envp);

// print_ast.c

void				print_redirect(t_redirect *redirect, int level, char *type);
void				print_assignments(t_assignment *assignment, int level);
void				print_command(char **cmd, int level);
void				print_ast_tree0(t_ast_node *node, int level);
const char			*getAstNodeTypeName(t_ast_node_type type);

// create_ast.c

t_ast_node			*create_ast(void);
t_ast_node			*create_node(void);
void				init_node(t_ast_node *new_node, t_ast_node_type node_type, \
							char **cmd, t_ast_node *new_node_left, \
							t_ast_node *new_node_right);
t_ast_node_content	*create_node_content(void);
void				init_node_content(char **cmd, t_ast_node *new_node);
void				create_node_left(char *cmd_str, t_ast_node **new_node_left);
void				create_node_right(char *cmd_str, \
										t_ast_node **new_node_right);
void				create_node_pipe(t_ast_node **new_node_head, \
						t_ast_node *new_node_left, t_ast_node *new_node_right);

// free_ast.c

void				free_ast(t_ast_node *node);

#endif
