/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:02:13 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 21:21:20 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "common.h"
# include "get_next_line.h"

// exit_utils0.c

void				free_all(t_pipe *data);
void				free_2d_str_cmd_split(t_pipe *data);
void				free_str(t_pipe *data);
void				free_2d_str(t_pipe *data);
void				free_2d_str_func(char **str);


// exit_utils1.c

void				exit_error_cmd_notfound(int exit_code, char *error_msg, \
											t_pipe *data);
void				exit_error(int exit_code, char *error_msg, t_pipe *data);
void				exit_zero_exit_code(int exit_code, t_pipe *data);
void				error_do_next_iter(int exit_code, char *error_msg, \
										t_pipe *data);

#endif
