/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:34:12 by musenov           #+#    #+#             */
/*   Updated: 2023/03/01 12:20:12 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conversion_type(va_list args, const char frmt);
int	conversion(int *print_len, int *i, va_list args, const char frmt);
int	no_conversion(int *print_len, const char str);

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	args;
	int		print_len;

	print_len = 0;
	i = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%' && ft_strchr("cspdiuxX%", s[i + 1]) != 0)
		{
			if (conversion(&print_len, &i, args, s[i + 1]) == -1)
				return (-1);
		}
		else
		{
			if (no_conversion(&print_len, s[i]) == -1)
				return (-1);
		}
		i++;
	}
	va_end(args);
	return (print_len);
}

int	conversion(int *print_len, int *i, va_list args, const char frmt)
{
	int		nr_of_chars;

	nr_of_chars = conversion_type(args, frmt);
	if (nr_of_chars == -1)
		return (-1);
	*print_len += nr_of_chars;
	*i = *i + 1;
	return (*print_len);
}

int	no_conversion(int *print_len, const char str)
{
	int		nr_of_chars;

	nr_of_chars = ft_putchar(str);
	if (nr_of_chars == -1)
		return (-1);
	*print_len += nr_of_chars;
	return (*print_len);
}

int	conversion_type(va_list args, const char frmt)
{
	if (frmt == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (frmt == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (frmt == 'p')
		return (ft_put_ptr(va_arg(args, void *)));
	else if (frmt == 'd' || frmt == 'i')
		return (ft_put_nmbr(va_arg(args, int)));
	else if (frmt == 'u')
		return (ft_put_nmbr_unsigned(va_arg(args, unsigned int)));
	else if (frmt == 'x')
		return (ft_put_nmbr_hex_lower(va_arg(args, unsigned int)));
	else if (frmt == 'X')
		return (ft_put_nmbr_hex_upper(va_arg(args, unsigned int)));
	else if (frmt == '%')
		return (ft_putchar('%'));
	else
		return (-1);
}
