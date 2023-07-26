/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:52:39 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 02:49:36 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
			(*new).next = *lst;
		*lst = new;
	}
}

/*

ft_lstadd_front:

PARAMETERS
lst: The address of a pointer to the first link of a list.
new: The address of a pointer to the node to be added to the list.

RETURN VALUE
None

DESCRIPTION
Adds the node ’new’ at the beginning of the list.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_back;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lst_back = ft_lstlast(*lst);
	(*lst_back).next = new;
}

ALTERNATIVE SOLUTION
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	(*new).next = *lst;
	*lst = new;
}

EXPLANATION
-/-

REMARK
-/-

*/