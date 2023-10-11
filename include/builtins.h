/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:38:02 by musenov           #+#    #+#             */
/*   Updated: 2023/10/11 19:01:23 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "common.h"

// builtin_calls.c

bool			is_builtin(char *cmd);
int				execute_bltn(t_minishell *shell, char **cmd);

// builtin_utils.c

// echo
char			*ft_strjoin_sym(const char *s1, const char *s2, char c);
void			free_p(char	*p);
void			internal_error_printer(char *msg);
// export
int				get_arg_count(char **cmd);
void			error_printer(char *cmd, char *arg, char *msg);
t_envp_ll		*get_var_list_node(t_envp_ll *var_head, char *str);
int				modify_var_list_node(t_envp_ll *matching_node, char *cmd);
int				add_to_var_list(t_envp_ll *var_list, char *str, int flag);
// static int		ft_sub_len(char const *start, char c);
int				ft_sub_len(char const *start, char c);

// echo.c

int				check_option_n(char **arg);
int				builtin_echo_strjoin(char **cmd, int cnt, int option_n);
int				echo_bltn(char **cmd);

// export.c

// static void		export_no_args(t_envp_ll *var_head);
// static int		is_valid_identifier(char *cmd);
// static int		export_one(t_envp_ll *var_head, char *cmd);
int				export_bltn(t_envp_ll *var_head, char **cmd);



#endif
