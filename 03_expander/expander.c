/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:09:29 by musenov           #+#    #+#             */
/*   Updated: 2023/11/20 19:00:15 by nnavidd          ###   ########.fr       */
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

int	ft_chrcmp(char *str)
{
	int	i;

	i = 0;

	while (str[i] != '\0')
	{
		if (strchr(SP_CHR, str[i]) != NULL)
			return (1);
		i++;
	}
	return (0);
}
/* 
char	*get_env_var(t_minishell *sh, char *var)
{
	t_envp_ll	*tmp;

	if (var == NULL)
		return (NULL);
	tmp = sh->envp_ll;
	while (tmp)
	{
		if ((ft_chrcmp(var) || (var[ft_strlen(var) - 1] == '\n' && \
		!ft_strncmp(tmp->var, var, ft_strlen(var) - 1))) && \
		!ft_strncmp(tmp->var, var, ft_strlen(tmp->var)))
			return (ft_strdup(tmp->value));
		if (ft_strcmp(tmp->var, var))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
} */

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	if (s1 == 0 || s2 == 0)
// 		return (0);
// 	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
// 	{
// 		s1++;
// 		s2++;
// 	}
// 	if (*s1 || *s2)
// 		return (0);
// 	return (1);
// }
			// printf("\nvar=%s\ntmp_var: %s\ntmp_value:%s\nthe value is:%d\n\n"
//,var ,tmp->var, tmp->value, ft_strncmp(tmp->var, var, ft_strlen(tmp->var)));

char	*get_env_var(t_minishell *sh, char *var)
{
	t_envp_ll	*tmp;

	if (var == NULL)
		return (NULL);
	tmp = sh->envp_ll;
	while (tmp)
	{
		if ((ft_chrcmp(var) || (var[ft_strlen(var) - 1] == '\n' && \
		!ft_strncmp(tmp->var, var, ft_strlen(var) - 1))) && \
		!ft_strncmp(tmp->var, var, ft_strlen(tmp->var)))
			return (ft_strdup(tmp->value));
		else if (var[ft_strlen(var) - 1] == '$' && \
		(!ft_strncmp(tmp->var, var, ft_strlen(tmp->var)) && \
		!ft_strncmp(var, tmp->var, ft_strlen(var) - 1)))
		{
			return (ft_strdup(tmp->value));
		}
		else if (ft_strcmp(tmp->var, var))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

/* while characters in token value
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
// void expand(t_minishell *sh, char **str, int j, bool heredoc)
void	expand(t_minishell *sh, char **str, int j)
{
	int		i;
	char	*var;
	char	*value;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$' && ((*str)[i + 1] && (*str)[i + 1] != ' ' && \
			(*str)[i + 1] != '/'))
		{
			j = i + 2;
			if ((*str)[i + 1] == '?')
				value = ft_itoa(sh->data->exit_code);
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
// TOKEN_DOUBLE_QUOTE = 2
// TOKEN_WORD = 5
// TOKEN_SINGLE_QUOTE = 1
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
		if (!ft_strncmp(sh->tokens[i].value, "<<\0", 3))
			direct = i;
		if (((sh->tokens[i].type == 2) || (sh->tokens[i].type == 5)) && \
		direct < 0 && !(sh->tokens[i].slash_number % 2))
			expand(sh, &sh->tokens[i].value, j);
		if (i + 1 < sh->token_len)
		{
			if ((sh->tokens[i].value[0] == '$' && sh->tokens[i].value[1] == \
			'\0' && sh->tokens[i].type == TOKEN_WORD) && \
			(sh->tokens[i + 1].type == TOKEN_SINGLE_QUOTE || \
			sh->tokens[i + 1].type == TOKEN_DOUBLE_QUOTE))
				erase_token(sh, i);
		}
		i++;
	}
}

// int ft_navid_strcmp(const char *src, const char *dst)
// {
//     char	*tmpsrc;
//     char	*tmpdst;

// 	tmpsrc = (char *)src;
// 	tmpdst = (char *)dst;
//     while (*tmpsrc && *tmpdst && *tmpsrc == *tmpdst)
// 	{
//         tmpsrc++;
// 		tmpdst++;
//     }
//     return (ft_strlen(tmpdst) + ft_strlen(tmpsrc));
// }

// char	*get_env_var(t_minishell *sh, char *var, bool heredoc)