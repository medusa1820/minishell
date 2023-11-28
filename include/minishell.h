/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:14:36 by musenov           #+#    #+#             */
/*   Updated: 2023/11/28 14:02:53 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "data_init.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "utils.h"
# include "builtins.h"

extern char			**environ;
extern volatile int	g_sig_nbr;

// main0.c

int			process_line(t_minishell *shell_data, t_pipe *data, char *line);
int			process_non_cmd(t_minishell *shell_data, t_pipe *data, int *i);
int			process_cmd(t_minishell *shell_data, t_pipe *data, int *i);
void		process_input(t_minishell *shell_data, t_pipe *data);
int			main(int argc, char **argv);

// main1.c

char		*get_input_line(t_pipe *data);
int			ft_isspace(int c);
bool		ms_line_has_input(char *line);
int			cleanup_and_exit(t_minishell *shell_data, t_pipe *data);
void		init_shell_and_pipe(t_minishell *shell_data, t_pipe *data);

/* 
int			main(int argc, char **argv);
int			main(int argc, char **argv, char **envp);
void		run_minishell_interactive(t_pipe *data, t_minishell *shell_data);
void		run_minishell_non_interactive(t_pipe *data, t_minishell *shell_data);
*/

#endif
