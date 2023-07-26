/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_nmbr_base_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:25:17 by musenov           #+#    #+#             */
/*   Updated: 2023/02/28 20:35:08 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_u_nmbr_base_len(unsigned long int n, size_t base)
{
	size_t	i;

	i = 1;
	while (n >= (unsigned long int)base)
	{
		n = n / base;
		i++;
	}
	return (i);
}
