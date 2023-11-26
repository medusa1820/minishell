/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:01:07 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 19:09:35 by musenov          ###   ########.fr       */
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

void	print_error_bltn(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	if (arg && *arg)
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

int	ft_sub_len(char const *start, char c)
{
	int	len;

	len = 0;
	while (*(start + len) != 0 && *(start + len) != c)
		len++;
	return (len);
}

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

/*
	char	*ft_strndup_pt(const char *start, char *delimiter)
	Returns a pointer to a null-terminated byte string, which contains 
	copies of at most size bytes from the string pointed to by str
*/

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

////////////////////////////// unset //////////////////////////////

//								-//-

////////////////////////////// env //////////////////////////////

//								-//-

////////////////////////////// pwd //////////////////////////////

//								-//-

////////////////////////////// cd //////////////////////////////

// char	*get_envp_ll_var_value(t_envp_ll *head, char *var)
// {
// 	t_envp_ll	*temp;

// 	temp = head;
// 	while (temp)
// 	{
// 		if (ft_strncmp(temp->var, var, ft_strlen(var) + 1) == 0)
// 			return (temp->value);
// 		temp = temp->next;
// 	}
// 	return (NULL);
// }

// int	update_envp_ll_var_value(t_envp_ll *head, char *var, char* value)
// {
// 	t_envp_ll	*temp;

// 	temp = head;
// 	while (temp)
// 	{
// 		if (ft_strncmp(temp->var, var, ft_strlen(var) + 1) == 0)
// 		{
// 			if (temp->value)
// 				free(temp->value);
// 			temp->value = ft_strdup(value);
// 			if (temp->value == NULL)
// 				return (EXIT_FAILURE);
// 			break ;
// 		}
// 		temp = temp->next;
// 	}
// 	return (EXIT_SUCCESS);
// }

char	*get_value_for_key(t_envp_ll *var_head, const char *key)
{
	t_envp_ll	*tmp;
	char		*value;

	tmp = var_head;
	value = NULL;
	while (tmp)
	{
		if (ft_strcmp((const char *) tmp->var, key))
		{
			value = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (value);
}

int	change_value_for_key(t_envp_ll *var_head, char *key, char *new_value)
{
	t_envp_ll	*tmp;
	char		*value;

	tmp = var_head;
	value = ft_strdup(new_value);
	if (value == NULL)
		return (EXIT_FAILURE);
	while (tmp)
	{
		if (ft_strcmp((const char *) tmp->var, key))
		{
			free_p(tmp->value);
			tmp->value = value;
			break ;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

bool	check_if_in_var_list(t_envp_ll *var_head, char *key)
{
	t_envp_ll	*tmp;

	tmp = var_head;
	while (tmp)
	{
		if (ft_strcmp((const char *) tmp->var, key))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (0);
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (0);
	return (1);
}

////////////////////////////// exit //////////////////////////////

int	atoi_negative(char *c)
{
	if (*c == '-')
		return (-1);
	else
		return (1);
}

int	is_int_min(long long int neg_pos, \
		long long int intvalue, char c, long long int *data)
{
	if (neg_pos == -1 && intvalue * -10 - (c - '0') == LLONG_MIN)
	{
		*data = INT_MIN;
		return (1);
	}
	return (0);
}

int	ft_atoi_secure(const char *str, long long int *data)
{
	long long int		intvalue;
	long long int		neg_pos;
	char				*chr;

	intvalue = 0;
	neg_pos = 1;
	chr = (char *)str;
	while (chr && (*chr == ' ' || *chr == '\t'))
		chr++;
	if (chr && (*chr == '-' || *chr == '+') && *(chr + 1) != '\0')
		neg_pos = atoi_negative(chr++);
	while (chr && *chr != '\0')
	{
		if (!(*chr >= '0' && *chr <= '9'))
			return (EXIT_FAILURE);
		if (is_int_min(neg_pos, intvalue, *chr, data))
			return (EXIT_SUCCESS);
		if (intvalue > (LLONG_MAX - (*chr - '0')) / 10)
			return (EXIT_FAILURE);
		intvalue = intvalue * 10 + (*chr - '0');
		chr++;
	}
	*data = (int)(intvalue * neg_pos);
	return (EXIT_SUCCESS);
}
