/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:06:50 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 21:07:06 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_open(t_pipe *data, char *word, int word_type)
{
	char	*buffer;
	int		fd_here_doc;

	fd_here_doc = open("here_doc_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_here_doc < 0)
		exit_error(errno, "Error creating temporary here_doc_file", data);
	buffer = get_next_line(STDIN_FILENO);
	while (buffer)
	{
		if (ft_strlen(word) == ft_strlen(buffer) - 1 && \
		!ft_strncmp(buffer, word, ft_strlen(word)))
		{
			free(buffer);
			break ;
		}
		else
		{
			if (word_type == TOKEN_WORD)
				expand(data->shell_data, &buffer, 0);
			ft_putstr_fd(buffer, fd_here_doc);
		}
		free(buffer);
		buffer = get_next_line(STDIN_FILENO);
	}
	close(fd_here_doc);
}
