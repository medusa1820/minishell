/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:01:07 by musenov           #+#    #+#             */
/*   Updated: 2023/10/12 10:20:05 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////////////////////////// echo //////////////////////////////

char	*ft_strjoin_sym(const char *s1, const char *s2, char c)
{
	char	*test_path;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	test_path = malloc(s1_len + s2_len + 2);
	if (!test_path)
		return (NULL);
	while (s1 && *s1 != 0)
		*test_path++ = *s1++;
	*test_path = c;
	test_path++;
	while (*s2 != '\0')
		*test_path++ = *s2++;
	*test_path = '\0';
	return (test_path - s1_len - s2_len - 1);
}

void	free_p(char	*p)
{
	if (p)
		free(p);
}

void	internal_error_printer(char *msg)
{
	ft_putstr_fd("minishell: internal error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

////////////////////////////// export //////////////////////////////

int	get_arg_count(char **cmd)
{
	int	arg_count;

	arg_count = 0;
	while (cmd && *(cmd + arg_count) != NULL)
		arg_count++;
	return (arg_count);
}

void	error_printer(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

t_envp_ll	*get_var_list_node(t_envp_ll *var_head, char *str)
{
	t_envp_ll	*current;
	int			newkey_len;

	newkey_len = ft_sub_len(str, '=');
	current = var_head;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, str, newkey_len) == 0 \
			&& (int)ft_strlen(current->var) == newkey_len)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	modify_var_list_node(t_envp_ll *matching_node, char *cmd)
{
	char		*delimiter;
	char		*new_value;

	delimiter = ft_strchr(cmd, '=');
	if (delimiter != NULL)
	{
		new_value = ft_strdup(delimiter + 1);
		if (!new_value)
			return (internal_error_printer("Malloc failed"), EXIT_FAILURE);
		free(matching_node->value);
		matching_node->value = new_value;
	}
	return (EXIT_SUCCESS);
}

int	add_to_var_list(t_envp_ll *var_list, char *str, int flag)
{
	t_envp_ll		*new_node;
	char			*delim_pt;

	new_node = (t_envp_ll *)ft_calloc(1, sizeof(t_envp_ll));
	if (!new_node)
		return (internal_error_printer("Malloc failed"), EXIT_FAILURE);
	new_node->env_var = flag;
	delim_pt = ft_strchr(str, '=');
	if (delim_pt == NULL)
	{
		new_node->var = ft_strdup(str);
		if (!new_node->var)
		{
			free(new_node);
			return (internal_error_printer("Malloc failed"), EXIT_FAILURE);
		}
	}
	else if (full_assign(new_node, str, delim_pt) != 0)
		return (EXIT_FAILURE);
	ft_lstadd_back_ms(&var_list, new_node);
	return (0);
}

// static int	ft_sub_len(char const *start, char c)
int	ft_sub_len(char const *start, char c)
{
	int	len;

	len = 0;
	while (*(start + len) != 0 && *(start + len) != c)
		len++;
	return (len);
}

// static int	full_assign(t_envp_ll *new, char *word, char *delim_pt)
int	full_assign(t_envp_ll *new, char *word, char *delim_pt)
{
	new->var = ft_strdup_pt(word, delim_pt);
	if (!new->var)
	{
		free(new);
		return (internal_error_printer("Malloc failed"), EXIT_FAILURE);
	}
	new->value = ft_strdup(delim_pt + 1);
	if (!new->value)
	{
		free(new->var);
		free(new);
		return (internal_error_printer("Malloc failed"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	ft_lstadd_back_ms(t_envp_ll **var_list, t_envp_ll *new)
{
	t_envp_ll	*last;

	if (*var_list == 0)
	{
		*var_list = new;
		return ;
	}
	last = *var_list;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return ;
}

/* char	*ft_strndup_pt(const char *start, char *delimiter)
Returns a pointer to a null-terminated byte string, which contains 
copies of at most size bytes from the string pointed to by str */
char	*ft_strdup_pt(const char *start, char *delimiter)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = 0;
	if (!start || !delimiter || delimiter < start)
		return (NULL);
	while (start + len != delimiter && *(start + len) != '\0')
		len++;
	dst = ft_calloc(1, (len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = start[i];
		i++;
	}
	return (dst);
}
