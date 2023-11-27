/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:56:48 by musenov           #+#    #+#             */
/*   Updated: 2023/11/27 17:25:52 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////////////////////////// export //////////////////////////////

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

int	add_to_var_list(t_envp_ll *var_list, char *str, int flag)
{
	t_envp_ll		*new_node;
	char			*delim_pt;

	new_node = (t_envp_ll *)ft_calloc(1, sizeof(t_envp_ll));
	if (!new_node)
		return (print_internal_error("Malloc failed"), EXIT_FAILURE);
	new_node->env_var = flag;
	delim_pt = ft_strchr(str, '=');
	if (delim_pt == NULL)
	{
		new_node->var = ft_strdup(str);
		if (!new_node->var)
		{
			free(new_node);
			return (print_internal_error("Malloc failed"), EXIT_FAILURE);
		}
	}
	else if (full_assign(new_node, str, delim_pt) != 0)
		return (EXIT_FAILURE);
	ft_lstadd_back_ms(&var_list, new_node);
	return (0);
}

int	full_assign(t_envp_ll *new, char *word, char *delim_pt)
{
	new->var = ft_strdup_pt(word, delim_pt);
	if (!new->var)
	{
		free(new);
		return (print_internal_error("Malloc failed"), EXIT_FAILURE);
	}
	new->value = ft_strdup(delim_pt + 1);
	if (!new->value)
	{
		free(new->var);
		free(new);
		return (print_internal_error("Malloc failed"), EXIT_FAILURE);
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

/* void	add_to_list(t_envp_ll **head, char *var, char *value)
{
	t_envp_ll	*new_node;
	t_envp_ll	*temp;

	new_node = create_new_node(var, value);
	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
} */

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

////////////////////////////// pwd //////////////////////////////

//								-//-

////////////////////////////// unset //////////////////////////////

//								-//-
