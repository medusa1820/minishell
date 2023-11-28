/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:38:02 by musenov           #+#    #+#             */
/*   Updated: 2023/11/28 11:13:21 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "common.h"

// builtin_calls.c

bool			is_builtin(char *cmd);
int				execute_bltn(t_minishell *shell, char **cmd);

// cd.c

int				cd_do(char *dir_path, t_envp_ll *envp_ll, bool dash_flag);
char			*check_cd_types(t_envp_ll *envp_ll, char **cmd, \
								bool *dash_flag);
int				check_vars_in_envp_ll(t_envp_ll *head);
int				cd_bltn(t_envp_ll *var_head, char **cmd, t_minishell *shell);

// echo.c

void			echo_print_strs(char **cmd, bool *n_option);
bool			check_n_option(char *cmd);
int				echo_bltn(char **cmd);

// env.c

int				env_bltn(char **envp_local, char **cmd);
// int			env_bltn(t_envp_ll *var_list, char **cmd);

// exit0.c

int				exit_bltn(t_minishell *shell, char **cmd);
int				exit_bltn_nbr_args_goe_2(char *str);
void			exit_bltn_nbr_args_e_1(char *str, \
										long long int *exit_code_local);
int				count_nbr_args(char **cmd);
bool			has_non_numeric_args(char *cmd);

// exit1.c

bool			white_space(int c);
bool			ft_atoi_ll_int(const char *str, long long int *result);
bool			arg_out_of_range(int neg, unsigned long long num);
void			free_before_exit(t_minishell *shell);

// export0.c

bool			valid_identifier(char *var); // rewrite
t_envp_ll		*find_var_node(t_envp_ll *head, char *cmd);
char			**make_var_value_pair(char *cmd);
int				export_var(t_envp_ll *head, char *cmd);
int				export_var_if_var_node(t_envp_ll *var_node, \
										char **var_value_pair);
void			export_no_args(t_envp_ll *var_head); // rewrite

// export1.c

int				export_bltn(t_envp_ll *head, char **cmd, t_minishell *shell);

// pwd.c

int				pwd_bltn(void);


// unset.c

bool			valid_identifier_unset(char *var);
int				unset_bltn(t_envp_ll *var_head, char **cmd, t_minishell *shell);
void			remove_node(t_envp_ll *head, t_envp_ll *node_to_unset);
void			free_node(t_envp_ll *node_to_unset);

// builtin_utils0.c

//											cd

char			*get_envp_ll_var_value(t_envp_ll *head, char *var);
int				update_envp_ll_var_value(t_envp_ll *head, char *var, \
										char *value);
int				ft_strcmp(const char *s1, const char *s2);

//											echo

void			print_internal_error(char *msg);

//											env

////			-//-

//											exit

////			-//-

// builtin_utils1.c

//											export

void			print_error_bltn(char *cmd, char *arg, char *msg);

//											pwd

////			-//-

//											unset

////			-//-

#endif
