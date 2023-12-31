/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_utils0.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:21:08 by musenov           #+#    #+#             */
/*   Updated: 2023/11/28 18:45:39 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_cmd_path(t_pipe *data, char **envp)
{
	if (data->cmd_split && \
		(ft_strnstr(data->cmd_split[0], "/", ft_strlen(data->cmd_split[0]))))
		prepare_cmd_path_slash(data);
	else
	{
		if (data->cmd_split)
		{
			if (ft_isalpha(data->cmd_split[0][0]) == 0 && \
				data->cmd_split[0][0] != '_')
			{
				exit_error_cmd_notfound(127, "Command not found: ", data);
			}
			else
			{
				prepare_paths(data, envp);
				prepare_cmd_path(data);
			}
		}
	}
}

void	prepare_paths(t_pipe *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && (ft_strnstr(envp[i], "PATH=", 5) == 0))
		i++;
	if (envp[i] == NULL)
	{
		data->paths = NULL;
		return ;
	}
	else
		data->paths = ft_split((envp[i] + 5), ':');
	if (data->paths == NULL)
		exit_error(5, "envp[i] split failed", data);
}

void	prepare_cmd_path(t_pipe *data)
{
	char	*cmd_path_func;
	char	*temp;
	int		i;

	temp = ft_strjoin("./", data->cmd_split[0]);
	if (access(temp, X_OK) != -1)
	{
		data->cmd_path = temp;
		return ;
	}
	free(temp);
	i = 0;
	while (data->paths && data->paths[i])
	{
		temp = ft_strjoin("/", data->cmd_split[0]);
		cmd_path_func = ft_strjoin(data->paths[i], temp);
		if (access(cmd_path_func, X_OK) != -1)
		{
			data->cmd_path = cmd_path_func;
			break ;
		}
		free_temp_and_cmd_path_func(temp, cmd_path_func);
		i++;
	}
	ft_exit_cmd_not_found(data, i);
}

void	free_temp_and_cmd_path_func(char *temp, char *cmd_path_func)
{
	free(temp);
	free(cmd_path_func);
}

void	prepare_cmd_path_slash(t_pipe *data)
{
	if (access(data->cmd_split[0], X_OK) != -1)
		data->cmd_path = data->cmd_split[0];
	else
		exit_error_cmd_notfound(127, "Command not found:", data);
}
