/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:17:00 by musenov           #+#    #+#             */
/*   Updated: 2023/11/22 16:01:06 by musenov          ###   ########.fr       */
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
