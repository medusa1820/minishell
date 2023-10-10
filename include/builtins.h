/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:38:02 by musenov           #+#    #+#             */
/*   Updated: 2023/10/10 15:28:45 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "common.h"

// builtin_calls.c

bool			is_builtin(char *cmd);
int				execute_bltn(t_minishell *shell, char **cmd);

// echo.c

int				check_option_n(char **arg);
int				builtin_echo_strjoin(char **cmd, int cnt, int option_n);
int				echo_bltn(char **cmd);

// builtin_utils.c

char			*ft_strjoin_sym(const char *s1, const char *s2, char c);
void			free_p(char	*p);
void			internal_error_printer(char *msg);

#endif
