/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:09:29 by musenov           #+#    #+#             */
/*   Updated: 2023/10/13 15:48:37 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	changing_var_value(char **str, char *value, int start, int len)
{
	char	*new;
	char	*left;
	char	*right;
	int		size;

	left = ft_substr(*str, 0, start);
	right = ft_strdup(*str + start + len);
	if (!left || !right)		
		return (free(left), free(right), start + len - 1);
	if (!value)
		value = "";
	size = ft_strlen(left) + ft_strlen(right) + ft_strlen(value) + 1;
	new = ft_calloc(size, sizeof(char));
	if (!new)
		return (free(left), free(right), start + len - 1);
	ft_strlcpy(new, left, size);
	ft_strlcat(new, value, size);
	ft_strlcat(new, right, size);
	free(*str);
	*str = new;
	return (free(left), free(right), start + ft_strlen(value) - 1);
}

char	*get_env_var(t_minishell *sh, char *var)
{
	t_envp_ll	*tmp;

	if (var == NULL)
		return (NULL);
	tmp = sh->envp_ll;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, var, ft_strlen(tmp->var)))
				return (ft_strdup(tmp->value)); 
		tmp = tmp->next;
	}
	return (NULL);
}

/*
while characters in token value
	if c == '$' && c + 1 == ('?' || '_' || alpha)
		len = 2
		while (c + len != (alphanumeric || '_'))
			len++;
		var = from first char + len
		get value from var
		if val == NULL -> val is empty
		insert val into var location while keeping everything aroung var 
		(copy before var to new, append val, append rest after var - free old save new)
*/
void	expand(t_minishell *sh, char **str, int j)
{
	int		i;
	char	*var;
	char	*value;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$')// && (*str)[i + 1])
		{
			value = NULL;
			j = i + 2;
			if ((*str)[i + 1] == '?')
				value = ft_itoa(sh->data->exit_code);// put the the correct exit code here
			else if ((*str)[i + 1] == '_' || ft_isalpha((*str)[i + 1]))
			{
				while ((*str)[j] == '_' || ft_isalnum((*str)[j]))
					j++;
				var = ft_substr(*str, i + 1, j - i);
				value = get_env_var(sh, var);
				free(var);
			}
			i = changing_var_value(str, value, i, j - i);
			free(value);
		}
	}
}

//ls -la |  < main.c << E < make cat >> out | $USER
void	expander(t_minishell *sh)
{
	int	i;
	int	j;
	int	direct;

	i = 0;
	j = 0;
	direct = -1;
	while (i < sh->token_len)
	{
		if (sh->tokens[i].type == TOKEN_REDIRECT)
			direct = i;
		if ((sh->tokens[i].type == TOKEN_DOUBLE_QUOTE) || \
			(sh->tokens[i].type == TOKEN_WORD))
		{
			if (direct >= 0 && !ft_strncmp(sh->tokens[direct].value, "<<", 2))
				continue;
			expand(sh, &sh->tokens[i].value, j);
			direct = -1;
		}
		i++;
	}
}
