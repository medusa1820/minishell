/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:00:12 by musenov           #+#    #+#             */
/*   Updated: 2023/11/07 15:37:05 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 

Use of chdir():

it sets sometimes errno to ESTALE ("Stale file handle") when a parent 
directory is removed on some systems. This is due to the inode table entry 
being recycled. 

	if (errno == ESTALE)
		errno = ENOENT;
	print_error_bltn("cd", dir_path, strerror(errno));

This is a fix to display "no such file or directory" 
error instead.

*/

int	cd_do(char *dir_path, t_envp_ll *envp_ll, bool dash_flag)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, PATH_MAX);
	if (update_envp_ll_var_value(envp_ll, "OLDPWD", cwd))
		return (EXIT_FAILURE);
	if (chdir(dir_path) != 0)
	{
		if (errno == ESTALE)
			errno = ENOENT;
		print_error_bltn("cd", dir_path, strerror(errno));
		return (EXIT_FAILURE);
	}
	free(cwd);
	cwd = getcwd(NULL, PATH_MAX);
	if (update_envp_ll_var_value(envp_ll, "PWD", cwd))
		return (EXIT_FAILURE);
	if (dash_flag)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}

char	*check_cd_types(t_envp_ll *envp_ll, char **cmd, bool *dash_flag)
{
	// char	*dir_path;

	// dir_path = NULL;
	if (!cmd[1] || ft_strncmp(cmd[1], "--", 3) == 0 || \
					ft_strncmp(cmd[1], "~", 2) == 0)
	{
		return (get_envp_ll_var_value(envp_ll, "HOME"));
	}
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
	{
		*dash_flag = true;
		return (get_envp_ll_var_value(envp_ll, "OLDPWD"));
	}
	else
		return (cmd[1]);
}

/*

QUESTION:

Can this 

char		*env_var_list[] = {"PWD", "OLDPWD", NULL};

be rewritten as this

char		*env_var_list[];

env_var_list[0] = "PWD";
env_var_list[1] = "OLDPWD";
env_var_list[2] = NULL;

???

ANSWER:

No, the syntax you've suggested isn't valid for initializing arrays in C.
In C, the size of an array needs to be known at compile time if you're 
initializing it at the point of declaration (unless you're using a flexible 
array member in a structure, but that's a special case and not applicable 
here). You can't declare an array without a size and then try to assign 
values to it like that.

The closest alternative with valid syntax would be to declare and 
initialize a pointer array and then assign values to it:

char *env_var_list[3];
env_var_list[0] = "PWD";
env_var_list[1] = "OLDPWD";
env_var_list[2] = NULL;

In this example, env_var_list is an array of char *, with space for three 
pointers. The pointers are then assigned to point to the string literals 
"PWD", "OLDPWD", and NULL.

It's important to note that in the original code:

char *env_var_list[] = {"PWD", "OLDPWD", NULL};

env_var_list is an array of pointers to string literals, and the size of 
the array is automatically determined by the number of initializers. This 
second approach with explicit assignments achieves the same result but 
requires writing more lines of code. The string literals "PWD" and "OLDPWD" 
are still stored in read-only memory, and the pointers in env_var_list point 
to them. This is a subtle but important detail, as attempting to modify 
these strings through the pointers would result in undefined behavior.

*/

int	check_vars_in_envp_ll(t_envp_ll *head)
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
	return (EXIT_SUCCESS);
}

int	cd_bltn(t_envp_ll *head, char **cmd)
{
	char	*dir_path;
	bool	dash_flag;

	dash_flag = false;
	if (check_vars_in_envp_ll(head))
		return (EXIT_FAILURE);
	dir_path = check_cd_types(head, cmd, &dash_flag);
	if (cd_do(dir_path, head, dash_flag))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
