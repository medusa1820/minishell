/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code_handler0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:25:57 by musenov           #+#    #+#             */
/*   Updated: 2023/11/18 19:42:16 by musenov          ###   ########.fr       */
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
				// return ;
			}
		}
	}
}

/*
int	ft_waiting(int *pids, int nr_of_forks)
{
	t_wait	s_wait;
	int		pid_index;

	pid_index = 0;
	while (pid_index < nr_of_forks)
	{
		if (pid_index == nr_of_forks - 1)
			waitpid(pids[pid_index], &s_wait.wstatus, 0);
		else
			waitpid(pids[pid_index], NULL, 0);
		pid_index++;
	}
	if (WIFEXITED(s_wait.wstatus))
	{
		s_wait.status_code = 0;
		s_wait.status_code = WEXITSTATUS(s_wait.wstatus);
		g_exit_code = s_wait.status_code;
	}
}
*/
