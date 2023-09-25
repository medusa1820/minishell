/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:27:01 by musenov           #+#    #+#             */
/*   Updated: 2023/09/25 18:09:52 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	forker_no_pipe(t_pipe *data, char **envp, t_ast_node *node)
{
	handle_in_redirections(data, node);
	handle_out_redirections(data, node);
	data->pid = fork();
	if (data->pid == -1)
		return (false);
	else
	{
		data->cmd_split = node->content->cmd;
		no_pipe(data, envp);
		return (true);
	}
}

void	here_doc_open(t_pipe *data, char *word)
{
	char	*buffer;
	int		fd_here_doc;

	fd_here_doc = open("here_doc_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_here_doc < 0)
		exit_error(errno, "Error creating temporary here_doc_file", data);
	ft_putstr_fd("here_doc>", STDOUT_FILENO);
	buffer = get_next_line(STDIN_FILENO);
	while (buffer)
	{
		if (ft_strlen(word) == ft_strlen(buffer) - 1 && \
		!ft_strncmp(buffer, word, ft_strlen(word)))
		{
			free(buffer);
			close(fd_here_doc);
			break ;
		}
		else
			ft_putstr_fd(buffer, fd_here_doc);
		free(buffer);
		ft_putstr_fd("here_doc>", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
	}
	close(fd_here_doc);
}
