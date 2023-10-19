/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:00:12 by musenov           #+#    #+#             */
/*   Updated: 2023/10/19 20:59:28 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* update_wds:
*	Updates the PWD and OLDPWD in the environment after a directory change.
*	A copy of the paths are stored internally for use in case the environment
*	variables are unset.
*/

/*

static void	update_wds(t_data *data, char *wd)
{
	set_env_var(data, "OLDPWD", get_env_var_value(data->env, "PWD"));
	set_env_var(data, "PWD", wd);
	if (data->old_working_dir)
	{
		free_ptr(data->old_working_dir);
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
	{
		free_ptr(data->working_dir);
		data->working_dir = ft_strdup(wd);
	}
	free_ptr(wd);
}

*/

/* change_dir:
*	Changes the current working directory and updates the
*	OLDPWD environment variable.
*	Returns 1 on success, 0 on failure.
*/

/*

static bool	change_dir(t_data *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		errmsg_cmd("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		ret = ft_strjoin(data->working_dir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wds(data, ret);
	return (true);
}

*/

/* cd_builtin:
	Executes the builtin cd command by changing the working directory.
	Returns 0 on success, 1 on failure.
*/

/*

int	cd_builtin(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var_value(data->env, "OLDPWD");
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (!change_dir(data, args[1]));
}

*/

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

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
static	bool	chdir_errno_mod(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	print_error_bltn("cd", path, strerror(errno));
	return (EXIT_FAILURE);
}

void	update_envp_ll_var_value(t_envp_ll *head, char *var, char* value)
{
	t_envp_ll	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strncmp(temp->var, var, ft_strlen(var) + 1))
		{
			if (temp->value)
				free(temp->value);
			temp->value = ft_strdup(value);
			break ;
		}
		temp = temp->next;
	}
}

int	cd_do(char *dir_path, t_envp_ll *envp_ll)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	update_envp_ll_var_value(envp_ll, "OLDPWD", cwd);
	if (chdir(dir_path) != 0)
		return (chdir_errno_mod(dir_path));
	free(cwd);
	cwd = getcwd(NULL, PATH_MAX);
	update_envp_ll_var_value(envp_ll, "PWD", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}

int	cd_bltn(t_envp_ll *envp_ll, char **cmd)
{
	char	*dir_path;

	if (!cmd[1] || ft_strncmp(cmd[1], "--", 3) == 0 || \
		ft_strncmp(cmd[1], "~", 2) == 0)
	{
		dir_path = get_envp_ll_var_value(envp_ll, "HOME");
		if (!dir_path)
		{
			print_error_bltn("cd", NULL, "HOME is not defined");
			return (EXIT_FAILURE);
		}
		return (cd_do(dir_path, envp_ll));
	}
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
	{
		dir_path = get_envp_ll_var_value(envp_ll, "OLDPWD");
		if (!dir_path)
		{
			print_error_bltn("cd", "-", "OLDPWD is not defined");
			return (EXIT_FAILURE);
		}
		return (cd_do(dir_path, envp_ll));
	}
	else
		return (cd_do(cmd[1], envp_ll));
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

int	cd_to_oldpwd(t_envp_ll *var_head, char *pwd)
{
	char	*oldpwd;

	oldpwd = get_value_for_key(var_head, "OLDPWD");
	if (oldpwd == NULL)
		return (free(pwd), \
		print_error_bltn("cd", NULL, "OLDPWD not set"), EXIT_FAILURE);
	if (oldpwd[0] == '\0')
		return (free(pwd), EXIT_SUCCESS);
	if (chdir(oldpwd) == -1)
		return (free(pwd), \
		print_error_bltn("cd", NULL, strerror(errno)), EXIT_FAILURE);
	oldpwd = ft_strdup(oldpwd);
	if (oldpwd == NULL)
		return (free(pwd), \
		internal_error_printer("Malloc failed"), EXIT_FAILURE);
	if (change_value_for_key(var_head, "OLDPWD", pwd))
		return (free(pwd), free(oldpwd), \
		internal_error_printer("Malloc failed"), EXIT_FAILURE);
	if (change_value_for_key(var_head, "PWD", oldpwd))
		return (free(pwd), free(oldpwd), \
		internal_error_printer("Malloc failed"), EXIT_FAILURE);
	ft_putendl_fd(oldpwd, STDOUT_FILENO);
	return (free(pwd), free(oldpwd), EXIT_SUCCESS);
}

int	cd_to_home(t_envp_ll *var_head, char *pwd)
{
	char	*home;

	home = get_value_for_key(var_head, "HOME");
	if (home == NULL)
		return (free(pwd), \
		print_error_bltn("cd", NULL, "HOME not set"), EXIT_FAILURE);
	if (home[0] == '\0')
		return (free(pwd), EXIT_SUCCESS);
	if (chdir(home) == -1)
	{
		free(pwd);
		if (errno == ENOENT)
			return (print_error_bltn("cd", home, strerror(errno)), EXIT_FAILURE);
		else
			return (print_error_bltn("cd", NULL, strerror(errno)), EXIT_FAILURE);
	}
	if (change_value_for_key(var_head, "OLDPWD", pwd))
		return (free(pwd), \
		internal_error_printer("Malloc failed"), EXIT_FAILURE);
	if (change_value_for_key(var_head, "PWD", home))
		return (free(pwd), \
		internal_error_printer("Malloc failed"), EXIT_FAILURE);
	return (free(pwd), EXIT_SUCCESS);
}

int	cd_with_path(t_envp_ll *var_head, char **cmd, char *pwd)
{
	if (chdir(cmd[1]) == -1)
	{
		free(pwd);
		if (errno == ENOENT)
			return (print_error_bltn("cd", cmd[1], strerror(errno)), EXIT_FAILURE);
		else
			return (print_error_bltn("cd", NULL, strerror(errno)), EXIT_FAILURE);
	}
	if (change_value_for_key(var_head, "OLDPWD", pwd))
		return (free(pwd), \
		internal_error_printer("Malloc failed"), EXIT_FAILURE);
	free(pwd);
	pwd = getcwd(NULL, PATH_MAX);
	if (pwd == NULL)
		return (print_error_bltn("cd", NULL, strerror(errno)), EXIT_FAILURE);
	if (change_value_for_key(var_head, "PWD", pwd))
		return (free(pwd), \
		internal_error_printer("Malloc failed"), EXIT_FAILURE);
	return (free(pwd), EXIT_SUCCESS);
}

int	execute_cd(t_envp_ll *var_head, char **cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, PATH_MAX);
	if (pwd == NULL)
		return (print_error_bltn("cd", NULL, strerror(errno)), EXIT_FAILURE);
	if (cmd[1] == NULL || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
		return (cd_to_home(var_head, pwd));
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		return (cd_to_oldpwd(var_head, pwd));
	else if (cmd[1][0] == '\0')
		return (free(pwd), EXIT_SUCCESS);
	else
		return (cd_with_path(var_head, cmd, pwd));
}

/*

int	cd_bltn(t_envp_ll *var_head, char **cmd)
{
	if (check_if_in_var_list(var_head, "PWD") != true)
	{
		if (add_to_var_list(var_head, "PWD", 0) != 0)
			return (EXIT_FAILURE);
	}
	if (check_if_in_var_list(var_head, "OLDPWD") != true)
	{
		if (add_to_var_list(var_head, "OLDPWD", 0) != 0)
			return (EXIT_FAILURE);
	}
	return (execute_cd(var_head, cmd));
}

*/