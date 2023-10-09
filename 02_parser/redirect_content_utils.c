/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_content_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:40:59 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/09 13:44:10 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect_type	redirect_type(char *str)
{
	t_redirect_type	type;

	type = UNDEFINED_TYPE;
	if (str[0] == '>' && str[1] == '>')
		type = REDIRECT_STDOUT_APPEND;
	else if (str[0] == '<' && str[1] == '<')
		type = REDIRECT_HERE_DOC;
	else if (str[0] == '<' && str[1] == 0)
		type = REDIRECT_STDIN;
	else if (str[0] == '>' && str[1] == 0)
		type = REDIRECT_STDOUT;
	// if (str)
	// 	free(str);
	return (type);
}

t_parser_state	add_redirect(t_redirect **redirect, \
t_redirect *new_redirection)
{
	t_redirect		*last_redirection;

	if (redirect == NULL || new_redirection == NULL)
		return (PARSER_FAILURE);
	if (*redirect == NULL)
		*redirect = new_redirection;
	else
	{
		last_redirection = *redirect;
		while (last_redirection->next != NULL)
			last_redirection = last_redirection->next;
		last_redirection->next = new_redirection;
	}
	return (PARSER_SUCCESS);
}
