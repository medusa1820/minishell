/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:41:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/08/03 20:28:35 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_value(t_split *sp, char *input_string)
{
	sp->input_copy = ft_strdup(input_string);
	sp->result = ft_calloc(sizeof(char *), ft_strlen (sp->input_copy));// it should be according to number of pipe sign
	if (!sp->result)
		exit(EXIT_FAILURE);
	sp->token_start = sp->input_copy;
	sp->p = sp->input_copy;
	sp->index = 0;
	sp->inside_quote = 0;
	sp->quote_char = '\0';
}

void	parse_string(t_split *sp)
{
	while (*sp->p != '\0')
	{
		if (*sp->p == '"' || *sp->p == '\'')
		{
			if (sp->quote_char == '\0' || sp->quote_char == *sp->p)
			{
				sp->inside_quote = !sp->inside_quote;
				sp->quote_char = *sp->p;
			}
		}
		else if (*sp->p == ' ' && !sp->inside_quote)
		{
			*sp->p = '\0';
			if (sp->token_start[0] != '\0')
			{
				sp->result[sp->index++] = ft_strdup(sp->token_start);
			}
			sp->token_start = sp->p + 1;
		}
		++sp->p;
	}
}

char	**sanitize(char **string, int len)
{
	int		i;
	char	*buff;

	i = 0;
	while (i < len)
	{
		if (string[i][0] == '\'')
		{
			buff = ft_strdup(string[i]);
			ft_strlcpy(string[i], buff + 1, ft_strlen(string[i]) - 1);
			free(buff);
		}
		i++;
	}
	return (string);
}

char	**split_string(char *input_string)
{
	t_split	sp;

	assign_value(&sp, input_string);
	parse_string(&sp);
	if (*sp.token_start != '\0')
	{
		sp.result[sp.index++] = ft_strdup(sp.token_start);
	}
	sp.result[sp.index] = 0;
	sanitize(sp.result, sp.index);
	return (sp.result);
}
