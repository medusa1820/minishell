/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:38:31 by musenov           #+#    #+#             */
/*   Updated: 2022/12/07 18:05:05 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if ((*lst).next == 0)
			return (lst);
		lst = (*lst).next;
	}
	return (lst);
}

/*

ft_lstlast:

PARAMETERS
lst: The beginning of the list.

RETURN VALUE
Last node of the list

DESCRIPTION
Returns the last node of the list.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if ((*lst).next == NULL)
			return (lst);
		lst = (*lst).next;
	}
	return (lst);
}

EXPLANATION
-/-

REMARK
-/-


*/