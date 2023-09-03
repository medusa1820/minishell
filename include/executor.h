/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:42:55 by musenov           #+#    #+#             */
/*   Updated: 2023/09/03 19:16:47 by musenov          ###   ########.fr       */
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

// child_process.c

void				first_cmd(t_pipe *data, char **envp);
void				middle_cmd(t_pipe *data, char **envp, int *i);
void				last_cmd(t_pipe *data, char **envp, int *i);

// child_process_utils0.c

void				find_cmd_path(t_pipe *data, char **envp);
void				prepare_paths(t_pipe *data, char **envp);
void				prepare_cmd_path(t_pipe *data);
void				prepare_cmd_path_slash(t_pipe *data);

// child_process_utils1.c

void				close_pipe0_fds(t_pipe *data);
void				close_pipe1_fds(t_pipe *data);

#endif
