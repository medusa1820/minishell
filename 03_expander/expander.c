/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:09:29 by musenov           #+#    #+#             */
/*   Updated: 2023/10/09 13:19:49 by nnavidd          ###   ########.fr       */
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
int ft_navid_strcmp(const char *src, const char *dst)
{
    char	*tmpsrc;
    char	*tmpdst;

	tmpsrc = (char *)src;
	tmpdst = (char *)dst;
    while (*tmpsrc && *tmpdst && *tmpsrc == *tmpdst)
	{
        tmpsrc++;
		tmpdst++;
    }
    return (ft_strlen(tmpdst) + ft_strlen(tmpsrc));
}

char	*get_env_var(t_minishell *sh, char *var, bool heredoc)
{
	t_envp_ll	*tmp;

	if (var == NULL)
		return (NULL);
	tmp = sh->envp_ll;
	while (tmp)
	{
		if (!heredoc && !ft_strncmp(tmp->var, var, ft_strlen(tmp->var)))
		{
			// printf("not heredoc\n");
				return (ft_strdup(tmp->value)); 
		}
		if (heredoc && ft_strcmp(tmp->var, var))
		{
			// printf("heredoc\n");
				return (ft_strdup(tmp->value)); 
		}
		tmp = tmp->next;
			// printf("hd:%d var:%s env_var:%s com:%d\n", heredoc, var, tmp->var, ft_navid_strcmp(tmp->var, var));
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
		insert val into var location while keeping everything aroung var (copy before var to new, append val, append rest after var - free old save new)
*/
void expand(t_minishell *sh, char **str, int j, bool heredoc)
{
	int		i;
	char	*var;
	char	*value;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$' && ((*str)[i + 1] && (*str)[i + 1] != ' '))
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
				value = get_env_var(sh, var, heredoc);
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
			if(!ft_strncmp(sh->tokens[i].value, "<<\0", 3))
				direct = i;
			// printf("size:%ld second char:%c next token type:%d\n", ft_strlen(sh->tokens[i].value), sh->tokens[i].value[1], sh->tokens[i + 1].type);
			// printf("i:%d len:%d\n", i, sh->token_len);
		if (((sh->tokens[i].type == TOKEN_DOUBLE_QUOTE) || (sh->tokens[i].type == TOKEN_WORD)) && direct < 0)
			expand(sh, &sh->tokens[i].value, j, false);
		// printf("token2:%s\n",sh->tokens[i].value);
		if (i + 1 < sh->token_len)
		{
			// printf("token2:%s\n",sh->tokens[i].value);
			if((sh->tokens[i].value[0] == '$' && sh->tokens[i].value[1] == '\0'\
			&& sh->tokens[i].type == TOKEN_WORD) &&\
			(sh->tokens[i + 1].type == TOKEN_SINGLE_QUOTE || \
			sh->tokens[i + 1].type == TOKEN_DOUBLE_QUOTE)) //&& 
			// (sh->tokens[i + 1].value[0] != '$' && sh->tokens[i + 1].value[1] != '\0'))
				erase_token(sh, i);
		}
		i++;
	}
}
