/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:42:55 by musenov           #+#    #+#             */
/*   Updated: 2023/10/01 15:19:19 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "common.h"
# include <termios.h>
# include <signal.h>

typedef enum e_ms_exit_code
{
	EC_SUCCESS = 0,
	EC_FAILURE = 1,
	EC_BUILTIN_BADUSAGE = 2,
	EC_COMMAND_NO_PERMISSION = 126,
	EC_COMMAND_NOT_FOUND = 127,
	EC_SIGNAL_INTERRUPT_BASE = 128,
	EC_SYNTAX_ERROR = 258,
	__EC_NO_SUCH_FILE = 300,
	__EC_IS_A_DIR = 301,
	__EC_INTERNAL_ERROR = 302,
}				t_ms_exit_code;

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
*/

volatile t_ms_exit_code	g_exit_code;

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

// child_process_utils2.c

void				first_pipe_in_out(t_pipe *data);
void				middle_pipe_in_out(t_pipe *data, int *i);
void				last_pipe_in_out(t_pipe *data, int *i);
void				dup2_fd_infile_std_in(t_pipe *data);
void				dup2_fd_outfile_std_out(t_pipe *data);

// exit_code_handler0.c

void				ft_waiting(t_pipe *data);

// signals0.c

int					ms_terminal_settings_change(void);
int					ms_terminal_settings_restore(void);
// void				ms_signal_handler_interative(int signum);
// int					ms_signal_handlers_interactive_set(void);

// signals1.c

// void				handle_sigquit(int signal);
// void				handle_sigint(int signal);
// void				handle_signals(void);

// signals2.c

void				set_signals_interactive(void);
void				ignore_sigquit(void);
void				signal_reset_prompt(int signo);
void				set_signals_noninteractive(void);
void				signal_print_newline(int signal);

#endif
