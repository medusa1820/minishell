/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:32:15 by musenov           #+#    #+#             */
/*   Updated: 2022/12/07 18:09:04 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp)
	{
		(*tmp).content = content;
		(*tmp).next = 0;
	}
	return (tmp);
}

/*

ft_lstnew:

PARAMETERS
content: The content to create the node with.

RETURN VALUE
The new node

DESCRIPTION
Allocates (with malloc(3)) and returns a new node. The member variable 
’content’ is initialized with the value of the parameter ’content’. 
The variable ’next’ is initialized to NULL.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp)
	{
		(*tmp).content = content;
		(*tmp).next = NULL;
	}
	return (tmp);
}

EXPLANATION
-/-

REMARK
-/-

*/