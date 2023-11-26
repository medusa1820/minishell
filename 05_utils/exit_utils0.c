/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:37:58 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 19:52:28 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_pipe *data)
{
	free_str(data);
	free_2d_str(data);
}

void	free_2d_str_cmd_split(t_pipe *data)
{
	if (data->cmd_split != NULL)
	{
		free_2d_str_func(data->cmd_split);
	}
}

void	free_str(t_pipe *data)
{
	if (data->cmd_path != NULL)
		free(data->cmd_path);
	data->cmd_path = NULL;
}

void	free_2d_str(t_pipe *data)
{
	if (data->paths != NULL)
		free_2d_str_func(data->paths);
}

void	free_2d_str_func(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}
