/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_nmbr_hex_lower.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:07:31 by musenov           #+#    #+#             */
/*   Updated: 2023/02/28 20:13:26 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_nmbr_hex_lower(unsigned long int n)
{
	char			*base;

	base = "0123456789abcdef";
	if (n >= 16)
	{
		if (ft_put_u_nmbr_base(n / 16, base) == -1 || \
			ft_put_u_nmbr_base(n % 16, base) == -1)
			return (-1);
	}
	else
		if (write(1, &base[n], 1) != 1)
			return (-1);
	return (ft_u_nmbr_base_len(n, 16));
}
