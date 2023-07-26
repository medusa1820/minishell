/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:13:59 by musenov           #+#    #+#             */
/*   Updated: 2023/02/21 14:06:02 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char	*s)
{
	int	i;

	i = 0;
	if (!s)
	{
		if (write(1, "(null)", 6) != 6)
			return (-1);
		return (6);
	}
	while (*(s + i))
		i++;
	if (write(1, s, i) != i)
		return (-1);
	return (i);
}
