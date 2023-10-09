/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:37:46 by musenov           #+#    #+#             */
/*   Updated: 2023/10/08 21:37:19 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* set_signals_interactive:
*	Sets the behavior in response to SIGINT (ctrl-c) and SIGQUIT (ctrl-\).
*	SIGINT resets the user input prompt to a new blank line.
*	SIGQUIT is ignored.
*	Used when minishell is in interactive mode, meaning it is awaiting
*	user input.
*/

void	set_signals_interactive(t_pipe *data)
// void	set_signals_interactive()
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

/*
void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
*/

void	signal_reset_prompt(int signo)
{
	// (void)signo;
	g_sig_nbr = signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// exit_error(g_sig_nbr, NULL, );
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
}

void	signal_reset_prompt_here_doc(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	// rl_on_new_line();
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
// void	set_signals_noninteractive()
{
	struct sigaction	act;

	data->interactive_mode = false;
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	// act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

/* signal_print_newline:
*	Prints a newline for noninteractive signal handling.
*/
// void	signal_print_newline(int signal)
// {
// 	(void)signal;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	// exit(1);
// }

void	signal_print_newline(int signal)
{
	g_sig_nbr = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	// exit(1);
}

/*

void	minishell_interactive(t_data *data)
{
	while (1)
	{
		set_signals_interactive();
		data->user_input = readline(PROMPT);
		set_signals_noninteractive();
		if (parse_user_input(data) == true)
			g_last_exit_code = execute(data);
		else
			g_last_exit_code = 1;
		free_data(data, false);
	}
}

*/