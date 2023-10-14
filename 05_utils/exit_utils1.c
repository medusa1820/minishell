/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:25:32 by musenov           #+#    #+#             */
/*   Updated: 2023/10/14 11:57:26 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_cmd_notfound(int exit_code, char *error_msg, t_pipe *data)
{
	dup2(2, STDOUT_FILENO);
	printf("%s%s: %s\n", error_msg, data->cmd_split[0], strerror(errno));
	free_ast(&data->shell_data->ast_root);
	free_all(data);
	free_envp_ll(data->shell_data->envp_ll);
	free_envp_local(data->shell_data->envp_local);
	exit(exit_code);
}
