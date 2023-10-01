/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:17:00 by musenov           #+#    #+#             */
/*   Updated: 2023/10/01 13:32:28 by musenov          ###   ########.fr       */
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












void	ms_signal_handler_interative(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// write(STDOUT_FILENO, "\nminishell$ ", 12);
	write(STDOUT_FILENO, RED "\nminishell> " RESET, strlen(RED) + 12 + \
													strlen(RESET));
	g_exit_code = EC_FAILURE;
}



int	ms_signal_handlers_interactive_set(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_RESTART;
	sigact.sa_handler = &ms_signal_handler_interative;
	sigaction(SIGINT, &sigact, NULL);
	// sigact.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigact, NULL);
	// sigaction(SIGTSTP, &sigact, NULL);
	return (EXIT_SUCCESS);
}













/*

void	ms_signal_handler_foreground_command(int signum)
{
	g_exit_code = ms_exit_code_from_signal(signum);
}

int	ms_signal_handlers_foreground_command_set(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_RESTART;
	sigact.sa_handler = &ms_signal_handler_foreground_command;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
	sigaction(SIGTSTP, &sigact, NULL);
	return (EXIT_SUCCESS);
}

*/

/*


#include "minishell.h"

// child process ctrl+C should display on terminal ^C
// mode 1 is disable, mode 0 is enable
void	set_termios(int mode)
{
	struct termios	ttr_settings;
	int				result;

	result = tcgetattr(STDOUT_FILENO, &ttr_settings);
	if (result < 0)
	{
		internal_error_printer("Tcgetattr() error");
		g_exit_code = 1;
		exit (EXIT_FAILURE);
	}
	if (mode == 1)
		ttr_settings.c_lflag &= ~ECHOCTL;
	else
		ttr_settings.c_lflag |= ECHOCTL;
	result = tcsetattr(STDOUT_FILENO, TCSANOW, &ttr_settings);
	if (result < 0)
	{
		internal_error_printer("Sigaction() error");
		g_exit_code = 1;
		exit (EXIT_FAILURE);
	}
}

static void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 1;
	}
}

static void	handle_signals_child(int signum)
{

	
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_code = 128 + SIGINT;
	}
	if (signum == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
		g_exit_code = 128 + SIGQUIT;
	}
}

void	set_signals(void)
{
	struct sigaction	sa;

	// g_sig_nmbr = SIGINT

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handle_signals;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Sigaction() error");
		g_exit_code = 1;
		exit (EXIT_FAILURE);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("Sigaction() error");
		g_exit_code = 1;
		exit (EXIT_FAILURE);
	}
}

void	set_signals_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handle_signals_child;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		internal_error_printer("Sigaction() error");
		g_exit_code = 1;
		exit (EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		internal_error_printer("Sigaction() error");
		g_exit_code = 1;
		exit (EXIT_FAILURE);
	}
}

*/






int	ms_terminal_settings_change(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ms_terminal_settings_restore(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (EXIT_FAILURE);
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
