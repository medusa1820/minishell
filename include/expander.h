/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:44:58 by musenov           #+#    #+#             */
/*   Updated: 2023/10/09 13:20:04 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "common.h"

// expander.c

int		changing_var_value(char **str, char *value, int start, int len);
char	*get_env_var(t_minishell *sh, char *var);
void 	expand(t_minishell *sh, char **str, int j);
void	expander(t_minishell *sh);

#endif
