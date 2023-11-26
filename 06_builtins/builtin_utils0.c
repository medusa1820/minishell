/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:01:07 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 21:37:06 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////////////////////////// cd //////////////////////////////

char	*get_envp_ll_var_value(t_envp_ll *head, char *var)
{
	t_envp_ll	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strncmp(temp->var, var, ft_strlen(var) + 1) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	print_error_bltn("cd", "-", "OLDPWD not set");
	return (NULL);
}

int	update_envp_ll_var_value(t_envp_ll *head, char *var, char *value)
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
	if (!temp)
	{
		if (add_to_var_list(head, var, 1))
			return (EXIT_FAILURE);
		update_envp_ll_var_value(head, var, value);
	}
	return (EXIT_SUCCESS);
}

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

////////////////////////////// env //////////////////////////////

//								-//-

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
