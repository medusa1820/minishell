/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:28:31 by musenov           #+#    #+#             */
/*   Updated: 2023/02/28 15:11:27 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_ptr(void	*ptr)
{
	unsigned long	p;

	p = (unsigned long)ptr;
	if (write(1, "0x", 2) != 2)
		return (-1);
	return (2 + ft_put_nmbr_hex_lower(p));
}
