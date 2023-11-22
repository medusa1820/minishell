/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:37:46 by musenov           #+#    #+#             */
/*   Updated: 2023/11/22 16:03:49 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signals_interactive(t_pipe *data)
{
	struct sigaction	act;

	data->interactive_mode = true;
	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

void	set_signals_interactive_here_doc(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt_here_doc;
	sigaction(SIGINT, &act, NULL);
}

/* ignore_sigquit:
*	Replaces SIGQUIT signals (ctrl-\) with SIG_IGN to ignore
*	the signal.
*/
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

/* signal_reset_prompt:
*	Resets the readline user input prompt for interactive signal handling.
*/

void	signal_reset_prompt(int signo)
{
	g_sig_nbr = signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	exit_code_signals(t_pipe *data)
{
	if (data->interactive_mode)
	{
		if (g_sig_nbr == 2)
			data->exit_code = 1;
	}
	else
	{
		if (g_sig_nbr == 2)
			data->exit_code = 128 + g_sig_nbr;
		if (g_sig_nbr == 3)
			data->exit_code = 128 + g_sig_nbr;
	}
	g_sig_nbr = 0;
}

void	signal_reset_prompt_here_doc(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

/* set_signals_noninteractive:
*	Sets the behavior in response to SIGINT (ctrl -c) and SIGQUIT (ctrl -\).
*	Used when minishell is in noninteractive mode, meaning it is not awaiting
*	user input. For example, when a command is running (i.e. cat), minishell
*	should not react to SIGINT and SIGQUIT because only the running process (cat)
*	needs to react to those signals.
*/

void	set_signals_noninteractive(t_pipe *data)
{
	struct sigaction	act;

	data->interactive_mode = false;
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	signal_print_newline(int signal)
{
	g_sig_nbr = signal;
	write(1, "\n", 1);
	rl_on_new_line();
}
