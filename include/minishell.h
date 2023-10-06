/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:14:36 by musenov           #+#    #+#             */
/*   Updated: 2023/10/06 23:46:17 by musenov          ###   ########.fr       */
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

extern char	**environ;

// main.c

int			main(int argc, char **argv);

void		run_minishell_interactive(t_pipe *data, t_minishell *shell_data);
void		run_minishell_non_interactive(t_pipe *data, \
											t_minishell *shell_data);


#endif
