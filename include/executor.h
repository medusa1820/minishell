/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:42:55 by musenov           #+#    #+#             */
/*   Updated: 2023/09/18 16:07:43 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "common.h"

// execute_ast.c

bool				execute_cmds(t_ast_node *head, int *i, t_pipe *data, \
								char **envp);
void				print_2d_array(char **cmd);
bool				forker(t_pipe *data, int *i, char **envp, t_ast_node *head);
bool				piper(t_pipe *data, int *i);
bool				forker_no_pipe(t_pipe *data, char **envp, t_ast_node *head);

// child_process.c

void				no_pipe(t_pipe *data, char **envp);
void				first_pipe(t_pipe *data, char **envp, t_ast_node *node);
t_redirect			*go_to_last_redirect(t_redirect *head);
void				here_doc_open(t_pipe *data, char *word);
void				middle_pipe(t_pipe *data, char **envp, int *i);
void				last_pipe(t_pipe *data, char **envp, int *i);

// child_process_utils0.c

void				find_cmd_path(t_pipe *data, char **envp);
void				prepare_paths(t_pipe *data, char **envp);
void				prepare_cmd_path(t_pipe *data);
void				prepare_cmd_path_slash(t_pipe *data);

// child_process_utils1.c

void				close_pipe0_fds(t_pipe *data);
void				close_pipe1_fds(t_pipe *data);

#endif
