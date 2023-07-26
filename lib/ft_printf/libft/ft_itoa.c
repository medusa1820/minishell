/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 09:44:44 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 17:01:53 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_prepare(int n, size_t *n_len, long *n_copy);

char	*ft_itoa(int n)
{
	char	*str;
	long	n_copy;
	size_t	n_len;

	str = ft_prepare(n, &n_len, &n_copy);
	if (!str)
		return (0);
	*(str + n_len--) = '\0';
	while (n_copy > 0)
	{
		*(str + n_len--) = n_copy % 10 + '0';
		n_copy = n_copy / 10;
	}
	if (n_len == 0 && *(str + 1) == '\0')
		*(str + n_len) = '0';
	else if (n_len == 0 && *(str + 1) != '\0')
		*(str + n_len) = '-';
	if (n == -2147483648)
		*(str + 10) = '8';
	return (str);
}

char	*ft_prepare(int n, size_t *n_len, long *n_copy)
{
	char	*mem_alloc;

	if (n > 0)
	{
		*n_len = 0;
		*n_copy = n;
	}
	else if (n <= 0 && n > -2147483648)
	{
		*n_len = 1;
		*n_copy = -n;
	}
	else
	{
		*n_len = 1;
		*n_copy = -(n + 1);
	}
	while (n)
	{
		n = n / 10;
		*n_len = *n_len + 1;
	}
	mem_alloc = (char *)malloc(sizeof(*mem_alloc) * (*n_len + 1));
	return (mem_alloc);
}

/*

ft_itoa:

PARAMETERS
-/-

RETURN VALUE
-/-

DESCRIPTION
-/-

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
-/-

EXPLANATION

char	*ft_itoa(int n)
{
	char	*str;
	long	n_copy;
	size_t	n_len;

	str = ft_prepare(n, &n_len, &n_copy);
	if (!str)
		return (0);

null-terminating the string "str"
	*(str + n_len--) = '\0';
	while (n_copy > 0)
	{

adding 'digits' starting from the end of string "str"
		*(str + n_len--) = n_copy % 10 + '0';
		n_copy = n_copy / 10;
	}

this is case for n = 0, and it is not considered in while loop 
above "while (n_copy > 0)"
	if (n_len == 0 && str[1] == '\0')
		*(str + n_len) = '0';

here we define the sign of the resulting string "number"
for n > 0 the n_len will be "-1" at this stage and for n < 0 the 
n_len will be "0". See how n_len is incremented for n > 0 and n <= 0
in ft_prepare()
	else if (n_len == 0 && str[1] != '\0')
		*(str + n_len) = '-';

this is the case for n = -2147483648, which is handeled in ft_prepare
like 
================	
	else
	{
		*n_len = 1;
		*n_copy = -(n + 1);
	}
================
so, n turns to be 2147483647 and its 10th digit is then swapped by 8
	
	if (n == -2147483648)
		*(str + 10) = '8';
	return (str);
}

REMARK
-/-

*/