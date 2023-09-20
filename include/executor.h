/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:42:55 by musenov           #+#    #+#             */
/*   Updated: 2023/09/20 18:44:18 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "common.h"

// execute_ast0.c

bool				execute_cmds(t_ast_node *head, int *i, t_pipe *data, \
								char **envp);
bool				forker(t_pipe *data, int *i, char **envp, t_ast_node *head);
bool				piper(t_pipe *data, int *i);
void				handle_in_redirections(t_pipe *data, t_ast_node *node);
void				handle_out_redirections(t_pipe *data, t_ast_node *node);

// execute_ast1.c

bool				forker_no_pipe(t_pipe *data, char **envp, t_ast_node *head);
void				here_doc_open(t_pipe *data, char *word);

// child_process.c

void				no_pipe(t_pipe *data, char **envp);
void				first_pipe(t_pipe *data, char **envp);
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
bool				data_has_infile(t_pipe *data);
bool				data_has_outfile(t_pipe *data);

#endif
