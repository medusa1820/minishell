/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:13:09 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 21:13:18 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_pipe(t_pipe *data, char **envp)
{
	if (data->pid == 0)
	{
		if (data->cmd_split)
		{
			find_cmd_path(data, envp);
			if (data_has_infile(data))
				dup2_fd_infile_std_in(data);
			if (data_has_outfile(data))
				dup2_fd_outfile_std_out(data);
			close_pipe0_fds(data);
			if (execve(data->cmd_path, data->cmd_split, envp) == -1)
				exit_error(errno, "Couldn't execute execve() no pipe", data);
		}
		close_pipe0_fds(data);
		exit_zero_exit_code(0, data);
	}
	close_pipe0_fds(data);
}
