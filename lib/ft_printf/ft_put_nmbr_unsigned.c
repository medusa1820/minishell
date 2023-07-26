/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_nmbr_unsigned.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:30:49 by musenov           #+#    #+#             */
/*   Updated: 2023/02/28 21:46:08 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_nmbr_unsigned(unsigned long int n)
{
	char					*base;
	unsigned long int		base_len;

	base = "0123456789";
	base_len = ft_strlen(base);
	if (n >= base_len)
	{
		if (ft_put_u_nmbr_base(n / base_len, base) == -1 || \
			ft_put_u_nmbr_base(n % base_len, base) == -1)
			return (-1);
	}
	else
		if (write(1, &base[n], 1) != 1)
			return (-1);
	return (ft_u_nmbr_base_len(n, base_len));
}
