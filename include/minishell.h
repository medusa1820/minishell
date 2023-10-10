/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:14:36 by musenov           #+#    #+#             */
/*   Updated: 2023/10/10 17:52:01 by musenov          ###   ########.fr       */
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

// main.c

int			main(int argc, char **argv);
// int	main(int argc, char **argv, char **envp);

void		run_minishell_interactive(t_pipe *data, t_minishell *shell_data);
void		run_minishell_non_interactive(t_pipe *data, \
											t_minishell *shell_data);


#endif
