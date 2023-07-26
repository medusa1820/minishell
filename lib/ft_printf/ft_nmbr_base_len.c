/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmbr_base_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:11:07 by musenov           #+#    #+#             */
/*   Updated: 2023/02/28 20:19:57 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_nmbr_base_len(long int n, size_t base_len)
{
	size_t	i;

	i = 1;
	while (n >= (long int)base_len)
	{
		n = n / base_len;
		i++;
	}
	return (i);
}
