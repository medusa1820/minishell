/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:19:49 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 21:25:11 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	if (!dst && dstsize == 0)
		return (0 + ft_strlen(src));
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	i = dst_len;
	j = 0;
	while (src[j] != '\0' && i < dstsize - 1)
	{
		dst[i++] = src[j++];
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}

/*

ft_strlcat:

PARAMETERS
-/-

RETURN VALUE
Like snprintf(3), the strlcpy() and strlcat() functions return the total 
length of the string they tried to create. For strlcat() that means the 
initial length of dst plus the length of src.

If the return value is >= dstsize, the output string has been truncated. 
It is the caller's responsibility to handle this.

DESCRIPTION
strlcat() appends string src to the end of dst.  It will append at most 
dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless 
dstsize is 0 or the original dst string was longer than dstsize (in practice 
this should not happen as it means that either dstsize is incorrect or that 
dst is not a proper string).

If the src and dst strings overlap, the behavior is undefined.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
-/-

EXPLANATION

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

// scenario 1: dstsize <= length(dst)

// ft_strlcat:    [OK] [OK] [OK] [OK] [OK] [OK] [OK] [OK] [OK] [OK] [OK] 
// [OK] [CRASH] 
// your strlcat crush when null parameter is sent with a size of 0
// test case: ft_strlcat(NULL, b, 0);

// scenario 1.a.: dst = NULL and dstsize =0

	if (!dst && dstsize == 0)
		return (0 + ft_strlen(src));

// scenario 1.b.:

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);

if dst_len >= dstsize, then there is no point to concatenate, as dstsize
is final size of dst after concatenation
	if (dstsize <= dst_len)
		return (dstsize + src_len);

// scenario 2: 

	i = dst_len;
	j = 0;
	while (src[j] != '\0' && i < dstsize - 1)
	{
		dst[i++] = src[j++];
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[j]));
}


REMARK
-/-

*/