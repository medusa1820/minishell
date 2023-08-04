/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:32:42 by musenov           #+#    #+#             */
/*   Updated: 2023/08/04 18:32:15 by musenov          ###   ########.fr       */
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
// # include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_ast_node_type
{
	AST_NODE_CMD,
	AST_NODE_PIPE
}	t_ast_node_type;

typedef enum e_redirect_type
{
	REDIRECT_STDIN,
	REDIRECT_STDOUT,
	REDIRECT_HERE_DOC,
	REDIRECT_STDOUT_APPEND
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*word;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_assignment
{
	char				*word;
	struct s_assignment	*next;
}	t_assignment;

typedef struct s_ast_node_content
{
	t_redirect		*stdin_redirect;
	t_redirect		*stdout_redirect;
	t_assignment	*assignments;
	char			**cmd;
}	t_ast_node_content;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	t_ast_node_content	*content;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_pipe
{
	int		pipe0_fd[2];
	int		pipe1_fd[2];
	pid_t	pid;
	int		nr_of_cmd_nodes;
	char	**paths;
	char	*cmd_path;
	char	**cmd_split;
}	t_pipe;

// main.c

int					main(int argc, char **argv, char **envp);

// print_ast.c

void				print_redirect(t_redirect *redirect, int level, char *type);
void				print_assignments(t_assignment *assignment, int level);
void				print_command(char **cmd, int level);
void				print_ast_tree0(t_ast_node *node, int level);
const char			*getAstNodeTypeName(t_ast_node_type type);

// create_ast.c

t_ast_node			*create_ast(void);
t_ast_node			*create_node(void);
void				init_node(t_ast_node *new_node, t_ast_node_type node_type, char **cmd, \
					t_ast_node *new_node_left, t_ast_node *new_node_right);
t_ast_node_content	*create_node_content(void);
void				init_node_content(char **cmd, t_ast_node *new_node);
void				create_node_left(char *cmd_str, t_ast_node **new_node_left);
void				create_node_right(char *cmd_str, t_ast_node **new_node_right);
void				create_node_pipe(t_ast_node **new_node_head, \
						t_ast_node *new_node_left, t_ast_node *new_node_right);

// free_ast.c

void				free_ast(t_ast_node *node);

// execute_ast.c

bool				execute_cmds(t_ast_node *head, int *i, t_pipe *data, \
								char **envp);
void				print_2d_array(char **cmd);
bool				forker(t_pipe *data, int *i, char **envp, t_ast_node *head);
// bool				forker(t_pipe **data, int *i, char **envp, t_ast_node *head);
bool				piper(t_pipe *data, int *i);

// child_process.c

void				first_cmd(t_pipe *data, char **envp);
void				middle_cmd(t_pipe *data, char **envp, int *i);
void				last_cmd(t_pipe *data, char **envp, int *i);

// child_process_utils0.c

void				find_cmd_path(t_pipe *data, char **envp);
void				prepare_paths(t_pipe *data, char **envp);
void				prepare_cmd_path(t_pipe *data);
void				prepare_cmd_path_slash(t_pipe *data);

// child_process_utils1.c

void				close_pipe0_fds(t_pipe *data);
void				close_pipe1_fds(t_pipe *data);

#endif
