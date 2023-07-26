/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:42:31 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 16:10:26 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	char	*ptr;
	size_t	i;

	s1_len = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (i < s1_len)
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

/*

ft_strdup:

PARAMETERS
-/-

RETURN VALUE
-/-

DESCRIPTION
The strdup() function allocates sufficient memory for a copy of the 
string s1, does the copy, and returns a pointer to it.  The pointer may 
subsequently be used as an argument to the function free(3).

If insufficient memory is available, NULL is returned and errno is 
set to ENOMEM.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
-/-

EXPLANATION
-/-

REMARK
-/-

*/