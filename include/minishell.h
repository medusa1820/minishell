/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:32:42 by musenov           #+#    #+#             */
/*   Updated: 2023/07/26 21:41:46 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/ft_printf/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
// # include "get_next_line.h"

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		nr_of_cmds;
	int		pipe0_fd[2];
	int		pipe1_fd[2];
	char	*cmd;
	char	**cmd_split;
	char	**paths;
	char	*cmd_path;
	pid_t	pid;
	bool	here_doc;
}	t_pipex;

int		main(int argc, char **argv, char **envp);












/*

// cmds.c
void	find_cmd_path(t_pipex *data, char **envp);
void	prepare_cmd_split(t_pipex *data);
void	prepare_paths(t_pipex *data, char **envp);
void	prepare_cmd_path(t_pipex *data);
void	prepare_cmd_path_slash(t_pipex *data);

// exit_error_free.c
void	exit_error(int exit_code, char *error_msg, t_pipex *data);
void	free_all(t_pipex *data);
void	free_str(t_pipex *data);
void	free_2d_str(t_pipex *data);
void	free_2d_str_func(char **str);

// get_next_line.c
char	*get_next_line(int fd);

// infile_outfile.c
void	get_fd_infile(char **argv, t_pipex *data);
void	here_doc_open(t_pipex *data, char **argv);
void	get_fd_outfile(char **argv, t_pipex *data);
// void	free_str1(char *str);
void	exit_error_cmd_notfound(int exit_code, char *error_msg, t_pipex *data);

// main.c
int		main(int argc, char **argv, char **envp);
void	init_data(t_pipex *data, int argc, char **argv);
void	pipex(t_pipex *data, int i, char **envp, char **argv);

// pid_funcs.c
void	first_cmd(t_pipex *data, char **envp, char **argv);
void	middle_cmd(t_pipex *data, char **envp, int i);
void	last_cmd(t_pipex *data, char **envp, int i, char **argv);
void	close_pipe0_fds(t_pipex *data);
void	close_pipe1_fds(t_pipex *data);

*/







#endif