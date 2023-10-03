/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:14:36 by musenov           #+#    #+#             */
/*   Updated: 2023/10/03 21:07:53 by musenov          ###   ########.fr       */
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

// main.c

// int			main(int argc, char **argv, char **envp);
int			main(int argc, char **argv);
// int			main(void);
void		run_minishell_interactive(t_pipe *data, t_minishell *shell_data);
void		run_minishell_non_interactive(t_pipe *data, \
											t_minishell *shell_data);


#endif
