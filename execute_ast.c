/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:11:03 by musenov           #+#    #+#             */
/*   Updated: 2023/08/04 00:30:45 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

Traversing the AST will be carried out recursively, starting from head it 
will check if the left node is a cmd, if not, then it goes to left node of the
node it checked previously and checks if it is cmd, if not, goes continues 
this way until it finds the node which has cmd. If, finally, the node is 
cmd, then it executes that node and closes and returns to the calling 
function. The calling function will then execute the right node. After the 
right node executed then algorithm goes to out calling function and executes 
again the right node and goes this way until it reaches the head node.

*/





/*

void	execute_cmds(t_ast_node *head, int *i, t_pipe *data)
{
	if (head == NULL)
		return ;
	if (head->type == AST_NODE_PIPE)
	{
		execute_cmds(head->left, i, data);
		print_2d_array(head->right->content->cmd);
		printf("i = %d\n", (*i)++);
	}
	else
	{
		print_2d_array(head->content->cmd);
		printf("i = %d\n", (*i)++);
		if (pipe(data->pipe0_fd) == -1)
			exit_error(errno, "Pipe failed", data);
		data->pid = fork();
		if (data->pid == -1)
			exit_error(errno, "Fork failed", data);
	}
}

*/

bool	execute_cmds(t_ast_node *head, int *i, t_pipe *data, char **envp)
{
	// printf("nr_of_cmd_nodes = %d\n", data->nr_of_cmd_nodes++);
	if (head == NULL)
		return (false);
	if (head->type == AST_NODE_PIPE)
	{
		if (execute_cmds(head->left, i, data, envp))
		{
			print_2d_array(head->right->content->cmd);
			printf("i = %d\n", (*i)++);
			


			
			// if (pipe(data->pipe0_fd) == -1)
			// 	return (false);
			// data->pid = fork();
			// if (data->pid == -1)
			// 	return (false);
			// return (true);
			return (piper(data, i) && forker(data, i, envp, head));
		}
		else
		{
			return (false);
		}
	}
	else
	{
		print_2d_array(head->content->cmd);
		printf("i = %d\n", (*i)++);

		// if (pipe(data->pipe0_fd) == -1)
		// 	return (false);
		// data->pid = fork();
		// if (data->pid == -1)
		// 	return (false);
		// return (true);
		return (piper(data, i) && forker(data, i, envp, head));
	}
}

void	print_2d_array(char **cmd)
{
	printf("content->cmd: ");
	while (*cmd)
	{
		printf("%s ", *cmd);
		cmd++;
	}
	printf("\n");
}

bool	piper(t_pipe *data, int *i)
{
	if (*i % 2 == 0)
	{
		if (pipe(data->pipe0_fd) == -1)
			return (false);
		return (true);
	}
	else
	{
		if (pipe(data->pipe1_fd) == -1)
			return (false);
		return (true);
	}
}

bool	forker(t_pipe *data, int *i, char **envp, t_ast_node *head)
{
	(void)i;
	data->pid = fork();
	if (data->pid == -1)
		return (false);
	else
	{
		// if (i == 0)
			// first_cmd(data, envp, argv);
			data->cmd_split = head->content->cmd;
			first_cmd(data, envp);
		// else if (i == data->nr_of_cmd_nodes - 1)
		// 	last_cmd(data, envp, i, argv);
		// else
		// 	middle_cmd(data, envp, i);



		// if (i == data->nr_of_cmd_nodes - 1)
		// 	last_cmd(data, envp, i, argv);
		// else if (i == 0)
		// 	first_cmd(data, envp, argv);
		// else
		// 	middle_cmd(data, envp, i);
		exit(1);
		return (true);
	}
}

/*

void	pipex(t_pipex *data, int i, char **envp, char **argv)
{
	if (data->here_doc)
		data->cmd = argv[i + 3];
	else
		data->cmd = argv[i + 2];
	if (i % 2 == 0)
	{
		if (pipe(data->pipe0_fd) == -1)
			exit_error(errno, "Pipe failed", data);
	}
	else
	{
		if (pipe(data->pipe1_fd) == -1)
			exit_error(errno, "Pipe failed", data);
	}
	data->pid = fork();
	if (data->pid == -1)
		exit_error(errno, "Fork failed", data);
	if (i == data->nr_of_cmds - 1)
		last_cmd(data, envp, i, argv);
	else if (i == 0)
		first_cmd(data, envp, argv);
	else
		middle_cmd(data, envp, i);
}

*/

void	first_cmd(t_pipe *data, char **envp)
{
	if (data->pid == 0)
	{
		// get_fd_infile(argv, data);
		find_cmd_path(data, envp);
		printf("data->cmd_path: %s", data->cmd_path);
		// dup2(data->fd_infile, STDIN_FILENO);
		
		
		// dup2(data->pipe0_fd[1], STDOUT_FILENO);
		
		
		// close_pipe0_fds(data);
		close(data->pipe0_fd[0]);
		// if (data->here_doc)
		// {
		// 	if (unlink("here_doc_file") == -1)
		// 		exit_error(errno, "Error deleting here_doc temp file", data);
		// }
		// close(data->fd_infile);




		// if (execve(data->cmd_path, data->cmd_split, envp) == -1)
		// 	exit_error(errno, "Couldn't execute execve() first", data);
		execve(data->cmd_path, data->cmd_split, envp);
	}
}

/*

void	middle_cmd(t_pipex *data, char **envp, int i)
{
	if (data->pid == 0)
	{
		find_cmd_path(data, envp);
		if (i % 2 == 0)
		{
			dup2(data->pipe1_fd[0], STDIN_FILENO);
			dup2(data->pipe0_fd[1], STDOUT_FILENO);
		}
		else
		{
			dup2(data->pipe0_fd[0], STDIN_FILENO);
			dup2(data->pipe1_fd[1], STDOUT_FILENO);
		}
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() middle", data);
	}
	if (i % 2 == 0)
		close_pipe1_fds(data);
	else
		close_pipe0_fds(data);
}

void	last_cmd(t_pipex *data, char **envp, int i, char **argv)
{
	if (data->pid == 0)
	{
		get_fd_outfile(argv, data);
		find_cmd_path(data, envp);
		if (i % 2 == 0)
			dup2(data->pipe1_fd[0], STDIN_FILENO);
		else
			dup2(data->pipe0_fd[0], STDIN_FILENO);
		dup2(data->fd_outfile, STDOUT_FILENO);
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		close(data->fd_outfile);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve() last", data);
	}
	close_pipe0_fds(data);
	close_pipe1_fds(data);
}

*/



void	close_pipe0_fds(t_pipe *data)
{
	close(data->pipe0_fd[0]);
	close(data->pipe0_fd[1]);
}

void	close_pipe1_fds(t_pipe *data)
{
	close(data->pipe1_fd[0]);
	close(data->pipe1_fd[1]);
}

void	find_cmd_path(t_pipe *data, char **envp)
{
	// prepare_cmd_split(data);
	prepare_paths(data, envp);
	if (ft_strnstr(data->cmd_split[0], "/", ft_strlen(data->cmd_split[0])))
		prepare_cmd_path_slash(data);
	else
		prepare_cmd_path(data);
}

// void	prepare_cmd_split(t_pipex *data)
// {
// 	data->cmd_split = ft_split(data->cmd, ' ');
// 	if (data->cmd_split == NULL)
// 		exit_error(4, "data.cmd split failed", data);
// }

void	prepare_paths(t_pipe *data, char **envp)
{
	int	i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	data->paths = ft_split((envp[i] + 5), ':');
	// if (data->paths == NULL)
	// 	exit_error(5, "envp[i] split failed", data);
}

void	prepare_cmd_path(t_pipe *data)
{
	char	*cmd_path_func;
	char	*temp;
	int		i;

	i = 0;
	while (data->paths[i])
	{
		temp = ft_strjoin("/", data->cmd_split[0]);
		cmd_path_func = ft_strjoin(data->paths[i], temp);
		free(temp);
		if (access(cmd_path_func, X_OK) != -1)
		{
			data->cmd_path = cmd_path_func;
			break ;
		}
		free(cmd_path_func);
		i++;
	}
	// if (data->paths[i] == NULL)
	// 	exit_error_cmd_notfound(127, "Command not found: ", data);
}

void	prepare_cmd_path_slash(t_pipe *data)
{
	if (access(data->cmd_split[0], X_OK) != -1)
		data->cmd_path = data->cmd_split[0];
	// else
	// 	exit_error_cmd_notfound(127, "Command not found:", data);
}
