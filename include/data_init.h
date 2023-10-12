/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:15:24 by musenov           #+#    #+#             */
/*   Updated: 2023/10/12 10:56:45 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_INIT_H
# define DATA_INIT_H

# include "common.h"

extern char					**environ;

// envp_ll_init.c

void		init_envp_linked_list(t_minishell *shell);
void		parse_env_string(char *str, char **var, char **value);
void		add_to_list(t_envp_ll **head, char *var, char *value);
t_envp_ll	*create_new_node(char *var, char *value);

// envp_ll_utils.c

void		print_envp_ll(t_envp_ll *head);
void		free_envp_ll(t_envp_ll *head);

// envp_local_init.c

void		envp_ll_to_envp_local(t_minishell *shell);
int			count_nodes(t_envp_ll *head);
char		*allocate_and_set_entry(t_envp_ll *node);

// envp_local_utils.c

void		print_envp_local(char **array);
void		free_envp_local(char **array);

// pipe_data.c

void		init_pipe_data(t_pipe *data, t_minishell *shell_data);
// void		init_pipe_data(t_pipe *data);

#endif
