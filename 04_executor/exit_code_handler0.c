/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code_handler0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:25:57 by musenov           #+#    #+#             */
/*   Updated: 2023/11/22 15:59:35 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_waiting(t_pipe *data)
{
	pid_t		wait_pid;
	int			status;

	wait_pid = 0;
	while (wait_pid != -1)
	{
		wait_pid = waitpid(-1, &status, 0);
		if (wait_pid == data->pid)
		{
			if (WIFEXITED(status))
			{
				data->exit_code = WEXITSTATUS(status);
				g_sig_nbr = 0;
			}
		}
	}
}
