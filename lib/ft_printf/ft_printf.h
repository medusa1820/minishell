/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:27:03 by musenov           #+#    #+#             */
/*   Updated: 2023/02/28 19:43:27 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>

# include <stdarg.h>
# include <limits.h>

# include "libft/libft.h"

int		ft_printf(const char *s, ...);

int		ft_putchar(char c);
int		ft_putstr(char *s);

int		ft_put_ptr(void	*ptr);
int		ft_put_nmbr_hex_lower(unsigned long int n);
int		ft_put_u_nmbr_base(unsigned long int n, const char *base);
size_t	ft_u_nmbr_base_len(unsigned long int n, size_t base);

int		ft_put_nmbr(long int n);
size_t	ft_nmbr_base_len(long int n, size_t base);

int		ft_put_nmbr_unsigned(unsigned long int n);

int		ft_put_nmbr_hex_upper(unsigned long int n);

#endif
