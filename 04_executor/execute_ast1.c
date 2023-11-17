/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:27:01 by musenov           #+#    #+#             */
/*   Updated: 2023/11/17 19:07:49 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	forker_no_pipe(t_pipe *data, char **envp, t_ast_node *node)
{
	int		saved_stdout;

	if (!handle_in_redirections(data, node))
		return (false);
	if (!handle_out_redirections(data, node))
		return (false);
	data->node = node;
	export_preps(data);
	if (data->cmd_split && is_builtin(data->cmd_split[0]))
	{
		// if (data_has_infile(data))
		// 	dup2_fd_infile_std_in(data);
		saved_stdout = dup(STDOUT_FILENO);
		if (data_has_outfile(data))
			dup2_fd_outfile_std_out(data);
		data->exit_code = execute_bltn(data->shell_data, data->cmd_split);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return (true);
	}
	data->pid = fork();
	if (data->pid == -1)
		return (false);
	else
	{
		no_pipe(data, envp);
		return (true);
	}
}












/*
void	here_doc_open(t_pipe *data, char *word, int	word_type)
{
	char	*buffer;
	int		fd_here_doc;
	int		j;

	j = 0;
	fd_here_doc = open("here_doc_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_here_doc < 0)
		exit_error(errno, "Error creating temporary here_doc_file", data);
	set_signals_interactive_here_doc();
	ms_terminal_settings_change();
	// ft_putstr_fd("here_doc> ", STDOUT_FILENO);
	buffer = get_next_line(STDIN_FILENO);
	// set_signals_noninteractive();
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
		{
			// if (word_type == TOKEN_WORD)
			// {
				// printf("this:%s and the type:%d\n", buffer, word_type);
				(void)word_type;
				expand(data->shell_data, &buffer, j, true);
			// }
			ft_putstr_fd(buffer, fd_here_doc);
		}
		free(buffer);
		// set_signals_interactive();
		// ft_putstr_fd("here_doc> ", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
		// set_signals_noninteractive();
	}
	close(fd_here_doc);
	ms_terminal_settings_restore();
}
*/






void	here_doc_open(t_pipe *data, char *word, int word_type)
{
	char	*buffer;
	int		fd_here_doc;
	int		j;

	j = 0;
	fd_here_doc = open("here_doc_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_here_doc < 0)
		exit_error(errno, "Error creating temporary here_doc_file", data);
	// set_signals_interactive_here_doc();
	ms_terminal_settings_change();
	// ft_putstr_fd("here_doc> ", STDOUT_FILENO);
	buffer = get_next_line(STDIN_FILENO);
	// set_signals_noninteractive();
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
		{
			if (word_type == TOKEN_WORD)
			{
				// printf("this:%s and the type:%d\n", buffer, word_type);
				// (void)word_type;
				// expand(data->shell_data, &buffer, j, true);
				expand(data->shell_data, &buffer, j);
			}
			ft_putstr_fd(buffer, fd_here_doc);
		}
		free(buffer);
		// set_signals_interactive();
		// ft_putstr_fd("here_doc> ", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
		// set_signals_noninteractive();
	}
	close(fd_here_doc);
	ms_terminal_settings_restore();
}







/*

// fill_heredoc:
// Copies user input into a temporary file. If user inputs an environment variable
// like $USER, expands the variable before writing to the heredoc.
// Returns true on success, false on failure.

bool	fill_heredoc(t_data *data, t_io_fds *io, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		set_signals_interactive();
		line = readline(">");
		set_signals_noninteractive();
		if (!evaluate_heredoc_line(data, &line, io, &ret))
			break ;
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
	free_ptr(line);
	return (ret);
}

*/













