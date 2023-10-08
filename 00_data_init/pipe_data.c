/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:45:12 by musenov           #+#    #+#             */
/*   Updated: 2023/10/06 23:47:34 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe_data(t_pipe *data, t_minishell *shell_data)
{
	data->cmd_path = NULL;
	data->paths = NULL;
	data->exit_code = 0;
	data->shell_data = shell_data;
}
