/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:37:46 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 21:01:11 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

1. **Ctrl-C (`^C`)**:

	- **Signal**: `SIGINT` (Interrupt)
	- **Description**: This is one of the most commonly used keystrokes in 
	the terminal. When you press `Ctrl-C`, it sends an interrupt signal to 
	the current foreground process running in the terminal. This signal 
	typically causes the process to terminate, allowing the user to 
	interrupt a running command. However, processes can choose to handle 
	this signal and act differently, or even ignore it.

2. **Ctrl-D (`^D`)**:

	- **Signal**: N/A
	- This keystroke does not correspond to a signal like 
	`Ctrl-C` or `Ctrl-\`. Instead, it's an EOF (End-of-File) character. 
	When you're inputting text into a terminal-based program and you press 
	`Ctrl-D`, you're signaling that you've finished your input. 
	For instance, if you're using the terminal itself and you press
	`Ctrl-D`, it typically means you're done inputting commands and you'd 
	like to close the terminal session (assuming there's no running 
	foreground process). In the context of reading from standard input 
	(like with the `cat` command without any arguments), `Ctrl-D`tells the 
	program you're done providing input.

3. Ctrl-\ (`^\`):

	- **Signal**: `SIGQUIT`

*/

void	set_signals_interactive(t_pipe *data)
{
	struct sigaction	act;

	data->interactive_mode = true;
	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

/*

Replace SIGQUIT (ctrl-\) with SIG_IGN to ignore the signal

*/

void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

/*

Resets the readline's input prompt

*/

void	signal_reset_prompt(int signo)
{
	g_sig_nbr = signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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
