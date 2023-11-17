/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:38:02 by musenov           #+#    #+#             */
/*   Updated: 2023/11/17 14:05:15 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "common.h"

// builtin_calls.c

bool			is_builtin(char *cmd);
int				execute_bltn(t_minishell *shell, char **cmd);

// echo.c

bool			check_n_option(char *cmd);
void			echo_print_strs(char **cmd, bool *n_option);
int				echo_bltn(char **cmd);

// env.c

int				env_bltn(t_envp_ll *var_list, char **cmd);

// pwd.c

int				pwd_bltn(void);

// cd.c

int				cd_bltn(t_envp_ll *var_head, char **cmd, t_minishell *shell);
int				check_vars_in_envp_ll(t_envp_ll *head);
char			*check_cd_types(t_envp_ll *envp_ll, char **cmd, \
								bool *dash_flag);
int				cd_do(char *dir_path, t_envp_ll *envp_ll, bool dash_flag);

// exit.c

int				exit_bltn(t_minishell *shell, char **cmd);
int				count_nbr_args(char **cmd);
bool			has_non_numeric_args(char *cmd);
bool			white_space(int c);
bool			ft_atoi_ll_int(const char *str, long long int *result);
bool			arg_out_of_range(int neg, unsigned long long num);
void			free_before_exit(t_minishell *shell);

// export.c

// int				export_bltn(t_envp_ll *var_head, char **cmd);
// void			export_preps(t_pipe *data);
// int				count_nmbr_assignments(t_ast_node *head);
// void			export_no_args(t_envp_ll *var_head);
// int				is_valid_identifier(char *cmd);
// int				export_one(t_envp_ll *var_head, char *cmd);

// export1.c

void			export_preps(t_pipe *data);
int				count_nmbr_assignments(t_ast_node *head);
int				export_bltn(t_envp_ll *head, char **cmd, t_minishell *shell);
// int				export_bltn(t_envp_ll *head, char **cmd);
void			export_no_args(t_envp_ll *var_head); // rewrite
bool			valid_identifier(char *var); // rewrite
int				export_var(t_envp_ll *head, char *cmd);
t_envp_ll		*find_var_node(t_envp_ll *head, char *cmd);
char			**make_var_value_pair(char *cmd);

// unset.c

int				unset_is_valid_identifier(char *cmd);
bool			valid_identifier_unset(char *var);
t_envp_ll		*get_previous(t_envp_ll *var_head, t_envp_ll *found_node);
void			free_single_var_node(t_envp_ll *node);
void			remove_found_node(t_envp_ll *var_head, t_envp_ll *found_node);
// int				unset_bltn(t_envp_ll *var_head, char **cmd);
int				unset_bltn(t_envp_ll *var_head, char **cmd, t_minishell *shell);
// void			remove_node(t_envp_ll *var_head, t_envp_ll *found_node);
void			remove_node(t_envp_ll *head, t_envp_ll *node_to_unset);
void			free_node(t_envp_ll *node_to_unset);

// builtin_utils.c

// echo +
char			*ft_strjoin_sym(const char *s1, const char *s2, char c);
void			free_p(char	*p);
void			internal_error_printer(char *msg);
// export
int				get_arg_count(char **cmd);
void			print_error_bltn(char *cmd, char *arg, char *msg);
t_envp_ll		*get_var_list_node(t_envp_ll *var_head, char *str);
int				modify_var_list_node(t_envp_ll *matching_node, char *cmd);
int				add_to_var_list(t_envp_ll *var_list, char *str, int flag);
int				ft_sub_len(char const *start, char c);
int				full_assign(t_envp_ll *new, char *word, char *delim_pt);
void			ft_lstadd_back_ms(t_envp_ll **var_list, t_envp_ll *new);
char			*ft_strdup_pt(const char *start, char *delimiter);

// cd

// char			*get_value_for_key(t_envp_ll *var_head, const char *key);
// int				change_value_for_key(t_envp_ll *var_head, char *key, char *new_value);
// bool			check_if_in_var_list(t_envp_ll *var_head, char *key);
int				ft_strcmp(const char *s1, const char *s2);

// exit
int				atoi_negative(char *c);
int				is_int_min(long long int neg_pos, long long int intvalue, \
							char c, long long int *data);
int				ft_atoi_secure(const char *str, long long int *data);
void			restore_redirect(int stdin_save, int stdout_save);










// builtin_utils1.c

// cd
int				update_envp_ll_var_value(t_envp_ll *head, char *var, \
										char *value);
char			*get_envp_ll_var_value(t_envp_ll *head, char *var);





#endif
