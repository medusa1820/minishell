/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:46 by musenov           #+#    #+#             */
/*   Updated: 2023/10/19 13:00:58 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_print_strs(char **cmd, bool *n_option)
{
	int		i;

	if (*n_option)
		i = 2;
	else
		i = 1;
	while (cmd[i])
	{
		if (!check_n_option(cmd[i]))
			break ;
		i++;
	}
	if (cmd[i])
		ft_putstr_fd(cmd[i++], STDOUT_FILENO);
	while (cmd[i])
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(cmd[i++], STDOUT_FILENO);
	}
	if (*n_option)
		return ;
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
}

bool	check_n_option(char *cmd)
{
	if (!cmd || *cmd != '-')
		return (false);
	cmd++;
	while (cmd && *cmd == 'n')
		cmd++;
	if (*cmd == '\0')
		return (true);
	return (false);
}

int	echo_bltn(char **cmd)
{
	bool	n_option;

	n_option = check_n_option(cmd[1]);
	echo_print_strs(cmd, &n_option);
	return (EXIT_SUCCESS);
}

/*

int	check_option_n(char **arg)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (*(arg + i) != NULL)
	{
		j = 1;
		if (arg[i][0] != '-')
			return (i);
		while (arg[i][j] != '\0')
		{
			if (arg[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	builtin_echo_strjoin(char **cmd, int cnt, int option_n)
{
	int		i;
	char	*tmp;
	char	*tmp_dup;

	i = 0;
	tmp_dup = NULL;
	while (cnt - i > 1 + option_n)
	{
		if (i == 0)
			tmp = ft_strdup(cmd[cnt - 1]);
		else
			tmp = ft_strjoin_sym(cmd[cnt - 1 - i], tmp_dup, ' ');
		if (tmp == NULL)
			return (free_p(tmp_dup), EXIT_FAILURE);
		free_p(tmp_dup);
		tmp_dup = ft_strdup(tmp);
		if (tmp_dup == NULL)
			return (free(tmp), EXIT_FAILURE);
		free(tmp);
		i++;
	}
	if (tmp_dup != NULL)
		ft_putstr_fd(tmp_dup, STDOUT_FILENO);
	return (free_p(tmp_dup), EXIT_SUCCESS);
}

int	echo_bltn(char **cmd)
{
	int		cnt;
	int		option_n;

	cnt = 0;
	option_n = 0;
	while (*(cmd + cnt) != NULL)
		cnt++;
	option_n = check_option_n(cmd + 1);
	if (cnt == 1)
	{
		if (option_n == 0)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	if (builtin_echo_strjoin(cmd, cnt, option_n))
		return (internal_error_printer("Malloc failed"), EXIT_FAILURE);
	if (option_n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

*/
