/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u_nmbr_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:14:10 by musenov           #+#    #+#             */
/*   Updated: 2023/02/28 19:39:12 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_u_nmbr_base(unsigned long int n, const char *base)
{
	unsigned long int		base_len;

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
