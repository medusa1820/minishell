/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:00:12 by musenov           #+#    #+#             */
/*   Updated: 2023/10/24 10:55:11 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envp_ll_var_value(t_envp_ll *head, char *var)
{
	t_envp_ll	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strncmp(temp->var, var, ft_strlen(var) + 1) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

/* chdir_errno_mod:
*	chdir can sometimes set errno to ESTALE ("Stale file handle")
*	when a parent directory is removed on some systems. This is due
*	to the inode table entry being recycled. This is a fix to display
*	"no such file or directory" error instead.
*/

static bool	chdir_errno_mod(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	print_error_bltn("cd", path, strerror(errno));
	return (EXIT_FAILURE);
}

int	update_envp_ll_var_value(t_envp_ll *head, char *var, char* value)
{
	t_envp_ll	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strncmp(temp->var, var, ft_strlen(var) + 1) == 0)
		{
			if (temp->value)
				free(temp->value);
			temp->value = ft_strdup(value);
			if (temp->value == NULL)
				return (EXIT_FAILURE);
			break ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	cd_do(char *dir_path, t_envp_ll *envp_ll, bool dash_flag)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, PATH_MAX);
	if (update_envp_ll_var_value(envp_ll, "OLDPWD", cwd))
		return (EXIT_FAILURE);
	if (chdir(dir_path) != 0)
		return (chdir_errno_mod(dir_path));
	free(cwd);
	cwd = getcwd(NULL, PATH_MAX);
	if (update_envp_ll_var_value(envp_ll, "PWD", cwd))
		return (EXIT_FAILURE);
	if (dash_flag)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}

int	cd_bltn_execute(t_envp_ll *envp_ll, char **cmd)
{
	char	*dir_path;
	bool	dash_flag;

	dash_flag = false;
	dir_path = NULL;
	if (!cmd[1] || ft_strncmp(cmd[1], "--", 3) == 0 || \
		ft_strncmp(cmd[1], "~", 2) == 0)
	{
		dir_path = get_envp_ll_var_value(envp_ll, "HOME");
		if (!dir_path)
			return (print_error_bltn("cd", NULL, "HOME is not defined"), \
					EXIT_FAILURE);
		return (cd_do(dir_path, envp_ll, dash_flag));
	}
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
	{
		dash_flag = true;
		dir_path = get_envp_ll_var_value(envp_ll, "OLDPWD");
		if (!dir_path)
			return (print_error_bltn("cd", "-", "OLDPWD is not defined"), \
					EXIT_FAILURE);
		return (cd_do(dir_path, envp_ll, dash_flag));
	}
	else
		return (cd_do(cmd[1], envp_ll, dash_flag));
}

// char		*env_var_list[] = {"PWD", "OLDPWD", NULL};

int	cd_bltn(t_envp_ll *head, char **cmd)
{
	char		*env_var_list[2];
	t_envp_ll	*temp;
	int			i;

	env_var_list[0] = "PWD";
	env_var_list[1] = "OLDPWD";
	i = 0;
	while (i < 2)
	{
		temp = head;
		while (temp)
		{
			if (ft_strncmp(temp->var, env_var_list[i], \
							ft_strlen(env_var_list[i]) + 1) == 0)
				break ;
			temp = temp->next;
		}
		if (!temp)
		{
			if (add_to_var_list(head, env_var_list[i], 0) != 0)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (cd_bltn_execute(head, cmd));
}
