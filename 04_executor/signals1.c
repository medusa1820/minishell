/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:12:48 by musenov           #+#    #+#             */
/*   Updated: 2023/10/01 13:15:53 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Handle ctrl+\
*/
void	handle_sigquit(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}

/*
Handle ctrl+c
*/
void	handle_sigint(int signal)
{
	(void)signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signals(void)
{
	struct sigaction	sa_sigquit;
	struct sigaction	sa_sigint;

	// remove_printing_signals();
	sa_sigquit.sa_handler = handle_sigquit;
	sa_sigint.sa_handler = handle_sigint;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
	sigaction(SIGINT, &sa_sigint, NULL);
}
