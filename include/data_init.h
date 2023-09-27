/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:15:24 by musenov           #+#    #+#             */
/*   Updated: 2023/09/27 22:11:42 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_INIT_H
# define DATA_INIT_H

# include "common.h"

extern char					**environ;

// envp_init0.c

void		init_envp_internal(t_minishell *shell);
void		parse_env_string(char *str, char **var, char **value);
void		add_to_list(t_envp_ll **head, char *var, char *value);
t_envp_ll	*create_new_node(char *var, char *value);
void		print_env_list(t_envp_ll *head);




#endif
