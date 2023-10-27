/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:12:11 by musenov           #+#    #+#             */
/*   Updated: 2023/10/27 21:09:22 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* is_valid_env_var_key:
*	Checks if the key is a valid name for an evironment
*	variable.
*	Returns true if the key contains only alphanumeric chars
*	or '_', or false if not.
*/
bool	valid_identifier(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

t_envp_ll	*find_var_node(t_envp_ll *head, char *cmd)
{
	t_envp_ll	*current;

	current = head;

	while (current != NULL)
	{
		if (ft_strncmp(current->var, cmd, ft_strlen(cmd) + 1) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/* void	make_sure_var_value_is_pair(char **var_value_pair)
{
	int		i;
	char	*temp1;
	char	*temp2;

	i = 0;
	while (var_value_pair[i])
		i++;
	if (i - 1 < 2)
		return ;
	else
	{
		while (i > 1)
		{
			temp1 = ft_strjoin('=', var_value_pair[i]);
			temp2 = ft_strjoin(var_value_pair[i - 1], temp1);
			free(var_value_pair[i - 1]);
			var_value_pair[i - 1] = temp2;
			free(temp1);
			free(temp1);
		}
	}
} */

char	**make_var_value_pair(char *cmd)
{
	char	*equal_sign;
	char	**var_value_pair;

	equal_sign = ft_strchr(cmd, '=');
	var_value_pair = (char **)malloc(sizeof(char *) * 3);
	var_value_pair[0] = ft_substr(cmd, 0, equal_sign - cmd);
	var_value_pair[1] = ft_substr(equal_sign, 1, ft_strlen(equal_sign));
	var_value_pair[2] = NULL;
	return (var_value_pair);
}

int	export_var(t_envp_ll *head, char *cmd)
{
	t_envp_ll	*var_node;
	char		**var_value_pair;

	var_value_pair = make_var_value_pair(cmd);
	// var_value_pair = ft_split(cmd, '=');
	// make_sure_var_value_is_pair(var_value_pair);
	var_node = find_var_node(head, var_value_pair[0]);
	if (var_node)
	{
		free(var_node->value);
		if (var_value_pair[1])
		{
			var_node->value = ft_strdup(var_value_pair[1]);
			if (!var_node->value)
			{
				free_2d_str_func(var_value_pair);
				return (EXIT_FAILURE);
			}
		}
		else
			var_node->value = ft_strdup("");
		var_node->env_var = true;
	}
	else if (var_value_pair[1])
		add_to_list(&head, var_value_pair[0], var_value_pair[1]);
	else
		add_to_list(&head, var_value_pair[0], "");
	free_2d_str_func(var_value_pair);
	return (EXIT_SUCCESS);
}

void	export_no_args(t_envp_ll *var_head)
{
	t_envp_ll	*current;

	current = var_head;
	while (current != NULL)
	{
		if (current->env_var == true)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(current->var, STDOUT_FILENO);
			if (current->value != NULL)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(current->value, STDOUT_FILENO);
				ft_putchar_fd('\"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		current = current->next;
	}
	return ;
}

/* export_builtin:
*	Adds the given variables to the environment variables.
*	Returns 0 if all args were successfully added to env,
*	or 1 if one or more args were not added to env.
*/
int	export_bltn(t_envp_ll *head, char **cmd)
{
	int		i;
	int		return_value;

	return_value = 0;
	i = 1;
	if (!cmd[i])
	{
		export_no_args(head);
		return (return_value);
	}
	while (cmd[i])
	{
		if (valid_identifier(cmd[i]))
		{
			if (ft_strchr(cmd[i], '='))
				export_var(head, cmd[i]);
		}
		else
		{
			print_error_bltn("export", cmd[i], "not a valid identifier");
			return_value = 1;
		}
		i++;
	}
	return (return_value);
}




/*

int	export_builtin(t_data *data, char **args)
{
	int		i;
	char	**tmp;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (env_builtin(data, NULL));
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			errmsg_cmd("export", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(args[i]);
			set_env_var(data, tmp[0], tmp[1]);
			free_str_tab(tmp);
		}
		i++;
	}
	return (ret);
}

*/
