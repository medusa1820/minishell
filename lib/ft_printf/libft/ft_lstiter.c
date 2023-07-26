/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:19:53 by musenov           #+#    #+#             */
/*   Updated: 2022/12/07 18:05:32 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f((*lst).content);
		lst = (*lst).next;
	}
}

/*

ft_lstiter:

PARAMETERS
lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.

RETURN VALUE
None

DESCRIPTION
Iterates the list ’lst’ and applies the function ’f’ on the content of 
each node.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f((*lst).content);
		lst = (*lst).next;
	}
}

EXPLANATION
-/-

REMARK
-/-

*/