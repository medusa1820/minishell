/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_content_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:43:01 by nnavidd           #+#    #+#             */
/*   Updated: 2023/11/28 12:51:16 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function reallocate the last cmd array, and add a new cmd to it. */

t_parser_state	feed_cmd_tokens(t_ast_node_content **content, t_minishell *sh)
{
	(*content)->cmd = ft_realloc_strings((*content)->cmd, \
			count_strings((*content)->cmd), sh->index);
	sh->index = count_strings((*content)->cmd);
	while (sh->head < sh->seg_end && sh->tokens[sh->head].type == TOKEN_WORD)
	{
		(*content)->cmd[sh->index++] = ft_strdup(sh->tokens[sh->head].value);
		free(sh->tokens[sh->head].value);
		sh->tokens[sh->head++].value = NULL;
		sh->token_len--;
	}
	(*content)->cmd[sh->index] = 0;
	return (PARSER_SUCCESS);
}

/* In the suffix function at the end of processing a segment according to the 
content type that are included in, the remain content treats in this function, 
thus first it is checked if they are assignment type, the they push to the 
assignment list, and cmd array, otherwise only cmd array will be feed. */

t_parser_state	feed_remained_cmd_tokens(t_ast_node_content **content, \
																t_minishell *sh)
{
	int	ret;
	int	tmp_head;
	int	tmp_segend;

	ret = PARSER_FAILURE;
	tmp_head = sh->head;
	tmp_segend = sh->seg_end;
	while (tmp_head < tmp_segend && sh->tokens[tmp_head].type != TOKEN_REDIRECT)
	{
		if (sh->tokens[tmp_head].type == TOKEN_ASSIGNMENT)
		{
			ret = parse_assignment(content, sh);
			if (ret == PARSER_FAILURE)
				break ;
			sh->head--;
			sh->token_len++;
			sh->tokens[tmp_head].type = TOKEN_WORD;
		}
		ret = parse_cmd_word(content, sh);
		if (ret == PARSER_FAILURE)
			break ;
		tmp_head++;
	}
	return (ret);
}

/* This function counts amount of the elements in an array of string. */

size_t	count_strings(char *strings[])
{
	size_t	count;

	count = 0;
	if (strings != NULL)
	{
		while (strings[count] != NULL)
			count++;
	}
	return (count);
}

/* This function reallocate an array of string from its old size to its
 new size.*/

char	**ft_realloc_strings(char **ptr, size_t old_count, size_t new_count)
{
	char	**new_ptr;
	size_t	copy_count;
	size_t	i;

	if (!ptr)
	{
		new_ptr = (char **) ft_calloc(new_count + 1, sizeof(char *));
		if (!new_ptr)
			return (freeing_cmd(new_ptr), NULL);
		return (new_ptr);
	}
	new_ptr = ft_calloc(old_count + new_count + 1, sizeof(char *));
	if (new_ptr == NULL)
		return (freeing_cmd(ptr), NULL);
	copy_count = old_count;
	i = -1;
	while (++i < copy_count)
	{
		new_ptr[i] = ft_strdup(ptr[i]);
		if (new_ptr[i] == NULL)
			return (freeing_cmd(new_ptr), NULL);
	}
	freeing_cmd(ptr);
	return (new_ptr);
}
