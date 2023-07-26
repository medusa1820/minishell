/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_nmbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:20:31 by musenov           #+#    #+#             */
/*   Updated: 2023/02/28 21:46:23 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_nmbr(long int n)
{
	const char	*base = "0123456789";
	int			a;
	int			nmbr_len;

	nmbr_len = 0;
	if (n < 0)
	{
		if (write(1, "-", 1) != 1)
			return (-1);
		a = ft_put_nmbr(-n);
		if (a == -1)
			return (-1);
		nmbr_len += a;
	}
	else if (n >= 10)
	{
		if ((ft_put_nmbr(n / 10) == -1) || \
			ft_put_nmbr(n % 10) == -1)
			return (-1);
	}
	else
		if (write (1, &base[n], 1) != 1)
			return (-1);
	nmbr_len += ft_nmbr_base_len(n, ft_strlen(base));
	return (nmbr_len);
}
