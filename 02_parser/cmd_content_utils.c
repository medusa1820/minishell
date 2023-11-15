/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_content_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:43:01 by nnavidd           #+#    #+#             */
/*   Updated: 2023/11/13 20:31:50 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_parser_state	feed_remained_cmd_tokens(t_ast_node_content **content, 
															// t_minishell *sh)
// {
// 	int	ret;
// 	int	tmp_head;
// 	int	tmp_segend;

// 	ret = PARSER_FAILURE;
// 	tmp_head = sh->head;
// 	tmp_segend = sh->seg_end;
// 	while (tmp_head < tmp_segend && sh->tokens[tmp_head].type != TOKEN_REDIRECT)
// 	{
// 		if (sh->tokens[tmp_head].type == TOKEN_ASSIGNMENT)
// 		{
// 			ret = parse_assignment(content, sh);
// 			if (ret == PARSER_FAILURE)
// 				break ;
// 		}
// 		else if (sh->tokens[tmp_head].type == TOKEN_WORD)
// 		{
// 			ret = parse_cmd_word(content, sh);
// 			if(ret == PARSER_FAILURE)
// 				break ;
// 		}
// 		tmp_head++;
// 	}
// 	return (ret);
// }

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

char    **ft_realloc_strings(char **ptr, size_t old_count, size_t new_count)
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

// char	**ft_realloc_strings(char **ptr, size_t old_count, size_t new_count)
// {
// 	char	**new_ptr;
// 	size_t	copy_count;
// 	size_t	i;

// 	if (!ptr)
// 	{
// 		new_ptr = (char **) ft_calloc(new_count + 2, sizeof(char *));
// 		if (!new_ptr)
// 			return (freeing_cmd(new_ptr), NULL);
// 		return (new_ptr);
// 	}
// 	new_ptr = ft_calloc(old_count + new_count + 2, sizeof(char *));
// 	if (new_ptr == NULL)
// 		return (freeing_cmd(ptr), NULL);
// 	copy_count = old_count;
// 	i = 0;
// 	while (i < copy_count)
// 	{
// 		new_ptr[i] = ft_strdup(ptr[i]);
// 		if (new_ptr[i] == NULL)
// 			return (freeing_cmd(new_ptr), NULL);
// 		i++;
// 	}
// 	freeing_cmd(ptr);
// 	return (new_ptr);
// }
