/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:24:46 by musenov           #+#    #+#             */
/*   Updated: 2023/10/17 19:30:43 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_value_recursive(t_envp_ll *head, const char *key)
{
	if (!head)
		return NULL;
	if (ft_strcmp((const char *)head->var, key))
		return head->value;
	return find_value_recursive(head->next, key);
}

char	*get_value_for_key(t_envp_ll *var_head, const char *key)
{
	return find_value_recursive(var_head, key);
}

int	set_value_recursive(t_envp_ll *head, char *key, char *value)
{
	if (!head)
		return EXIT_FAILURE;
	if (ft_strcmp((const char *)head->var, key))
	{
		free_p(head->value);
		head->value = value;
		return EXIT_SUCCESS;
	}
	return set_value_recursive(head->next, key, value);
}

int	change_value_for_key(t_envp_ll *var_head, char *key, char *new_value)
{
	char *value = ft_strdup(new_value);
	if (!value)
		return EXIT_FAILURE;
	return set_value_recursive(var_head, key, value);
}

bool	check_value_recursive(t_envp_ll *head, char *key)
{
	if (!head)
		return false;
	if (ft_strcmp((const char *)head->var, key))
		return true;
	return check_value_recursive(head->next, key);
}

bool	check_if_in_var_list(t_envp_ll *var_head, char *key)
{
	return check_value_recursive(var_head, key);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return 0;
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 || *s2) ? 0 : 1;
}

int	handle_cd_errors(char *pwd, char *path)
{
	free(pwd);
	if (errno == ENOENT)
		return error_printer("cd", path, strerror(errno));
	return error_printer("cd", NULL, strerror(errno));
}

int	cd_to_oldpwd(t_envp_ll *var_head, char *pwd)
{
	char *oldpwd = get_value_for_key(var_head, "OLDPWD");
	if (!oldpwd)
		return (free(pwd), error_printer("cd", NULL, "OLDPWD not set"));
	if (!oldpwd[0])
		return free(pwd);
	if (chdir(oldpwd) == -1)
		return handle_cd_errors(pwd, NULL);
	return change_pwd_values(var_head, pwd, oldpwd);
}

int	cd_to_home(t_envp_ll *var_head, char *pwd)
{
	char *home = get_value_for_key(var_head, "HOME");
	if (!home)
		return (free(pwd), error_printer("cd", NULL, "HOME not set"));
	if (!home[0])
		return free(pwd);
	if (chdir(home) == -1)
		return handle_cd_errors(pwd, home);
	return change_pwd_values(var_head, pwd, home);
}

int	cd_with_path(t_envp_ll *var_head, char **cmd, char *pwd)
{
	if (chdir(cmd[1]) == -1)
		return handle_cd_errors(pwd, cmd[1]);
	pwd = getcwd(NULL, PATH_MAX);
	if (!pwd)
		return error_printer("cd", NULL, strerror(errno));
	return change_pwd_values(var_head, pwd, cmd[1]);
}

int	execute_cd(t_envp_ll *var_head, char **cmd)
{
	char *pwd = getcwd(NULL, PATH_MAX);
	if (!pwd)
		return error_printer("cd", NULL, strerror(errno));
	return handle_cd_commands(var_head, cmd, pwd);
}

int	cd_bltn(t_envp_ll *var_head, char **cmd)
{
	if (!check_if_in_var_list(var_head, "PWD") && add_to_var_list(var_head, "PWD", 0))
		return EXIT_FAILURE;
	if (!check_if_in_var_list(var_head, "OLDPWD") && add_to_var_list(var_head, "OLDPWD", 0))
		return EXIT_FAILURE;
	return execute_cd(var_head, cmd);
}
