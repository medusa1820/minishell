/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:17:00 by musenov           #+#    #+#             */
/*   Updated: 2023/11/26 20:20:34 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
