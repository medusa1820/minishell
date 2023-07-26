/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:46:27 by musenov           #+#    #+#             */
/*   Updated: 2022/12/08 18:29:15 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (len > 0)
		{
			*((char *)dst + len - 1) = *((char *)src + len - 1);
			len--;
		}
	}
	else
	{
		i = 0;
		while (len - i > 0)
		{
			*((char *)dst + i) = *((char *)src + i);
			i++;
		}
	}
	return (dst);
}

/*

ft_memmove:

PARAMETERS
-/-

RETURN VALUE
The memmove() function returns the original value of dst.

DESCRIPTION
The memmove() function copies len bytes from string src to string dst. 
The two strings may overlap; the copy is always done in a non-destructive 
manner.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTIONs

1.

This solution creates a buffer where it stores the original value of src,
but it is not allowed to use malloc() in this task

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	*dst1;
	size_t	*src1;
	size_t	*src2;
	int		ii;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	src2 = (unsigned char *) malloc (ft_strlen ((const char *) src1) + 1);
	ii = 0;
	while (src1[ii] != '\0')
	{
		*(src2 + ii) = *(src1 + ii);
		ii = ii + 1;
	}
	*(src2 + ii) = '\0';
	i = 0;
	while (i < len)
	{
		*(dst1 + i) = *(src2 + i);
		i++;
	}
	free(src2);
	return (dst);
}

2.

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	if (dst == src)
		return (dst);
	d = dst;
	s = src;
	if (dst > src)
		while (len--)
			d[len] = s[len];
	else
		while (len--)
			*d++ = *s++;
	return (dst);
}

3.

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if ((unsigned char *)dst == NULL && (unsigned char *)src == NULL)
		return (NULL);
	if (dst > src)
	{
		while (len > 0)
		{
			((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1];
			len--;
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}


EXPLANATION

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

no matter how many elements copied from src, if src starts at dst, then
it will be the same, therefore dst itself is returned
	if (dst == src)
		return (dst);
	
address of pointer dst is greater than of src if dst is pointing
to a variable declared earlier than the one pointed by src
	if (dst > src)
	{
		while (len > 0)
		{
			*((char *)dst + len - 1) = *((char *)src + len - 1);
			len--;
		}
	}

this is for case src < dst. Alternatively the following can be written inside
while loop "while (len - i > 0)"
===========================
ft_memcpy(dst, src, len);
===========================

	else
	{
		i = 0;
		while (len - i > 0)
		{
			*((char *)dst + i) = *((char *)src + i);
			i++;
		}
	}
	return (dst);
}

REMARK
Memory overlap allowed, but decide to copy from begins or ends of strings

*/