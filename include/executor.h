/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:42:55 by musenov           #+#    #+#             */
/*   Updated: 2023/11/28 18:39:47 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "common.h"
# include <termios.h>
# include <signal.h>

/*

The g_exit_code variable is declared as volatile. The volatile keyword in C 
tells the compiler that a variable may change at any time without any action 
being taken by the code the compiler finds nearby. It's often used in the 
context of multi-threaded applications or signal handling, preventing the 
compiler from optimizing away subsequent reads or writes and thus making the 
programmer's intention clear that this variable can be changed externally.

In the context of signal handling, volatile ensures that if a signal handler 
changes the value of g_exit_code, then that change will be visible immediately 
to other parts of the code once the signal handler returns.

extern volatile int	g_sig_nbr;

*/

// child_process_utils0.c

void				find_cmd_path(t_pipe *data, char **envp);
void				prepare_paths(t_pipe *data, char **envp);
void				prepare_cmd_path(t_pipe *data);
void				free_temp_and_cmd_path_func(char *temp, \
												char *cmd_path_func);
void				prepare_cmd_path_slash(t_pipe *data);

// child_process_utils1.c

void				ft_exit_cmd_not_found(t_pipe *data, int i);
void				close_pipe0_fds(t_pipe *data);
void				close_pipe1_fds(t_pipe *data);
bool				data_has_infile(t_pipe *data);
bool				data_has_outfile(t_pipe *data);

// child_process_utils2.c

void				first_pipe_in_out(t_pipe *data);
void				middle_pipe_in_out(t_pipe *data, int *i);
void				last_pipe_in_out(t_pipe *data, int *i);
void				dup2_fd_infile_std_in(t_pipe *data);
void				dup2_fd_outfile_std_out(t_pipe *data);

// child_process0.c

void				first_pipe(t_pipe *data, char **envp);
void				middle_pipe(t_pipe *data, char **envp, int *i);
void				last_pipe(t_pipe *data, char **envp, int *i);
void				close_pipe_0_and_1_fds(t_pipe *data);
void				close_pipe_0_and_1_fds_for_last_pipe(t_pipe *data, int *i);

// child_process1.c

void				no_pipe(t_pipe *data, char **envp);

// execute_ast0.c

bool				execute_cmds(t_ast_node *head, int *i, t_pipe *data, \
								char **envp);
bool				piper(t_pipe *data, int *i);
bool				forker(t_pipe *data, int *i, char **envp, t_ast_node *head);
void				export_preps(t_pipe *data);
int					count_nmbr_assignments(t_ast_node *head);

// execute_ast1.c

bool				handle_redirections(t_pipe *data, t_ast_node *node, int *i);
bool				handle_in_redirections(t_pipe *data, t_ast_node *node);
bool				handle_out_redirections(t_pipe *data, t_ast_node *node);
bool				forker_no_pipe(t_pipe *data, char **envp, t_ast_node *head);
bool				handle_redirections_no_pipe(t_pipe *data, t_ast_node *node);

// execute_ast2.c

void				here_doc_open(t_pipe *data, char *word, int wrod_type);

// exit_code_handler0.c

void				ft_waiting(t_pipe *data);

// signals1.c

int					ms_terminal_settings_change(void);
int					ms_terminal_settings_restore(void);
void				exit_code_signals(t_pipe *data);

// signals0.c

void				set_signals_interactive(t_pipe *data);
void				ignore_sigquit(void);
void				signal_reset_prompt(int signo);
void				set_signals_noninteractive(t_pipe *data);
void				signal_print_newline(int signal);

#endif
