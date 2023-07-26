/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:48:14 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 18:04:20 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_back;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lst_back = ft_lstlast(*lst);
	(*lst_back).next = new;
}

/*

ft_lstadd_back:

PARAMETERS
lst: The address of a pointer to the first link of a list.
new: The address of a pointer to the node to be added to the list.

RETURN VALUE
None

DESCRIPTION
Adds the node ’new’ at the end of the list.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

ALTERNATIVE SOLUTION
-/-

EXPLANATION

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_back;

	if (!new)
		return ;
	
if *lst contains no address then put address of stored in new into
*lst
	if (!*lst)
	{
		*lst = new;
		return ;
	}

Returns the last node of the list.
	lst_back = ft_lstlast(*lst);

In parameter "next" put the pointer to node to be added to the list.
	(*lst_back).next = new;
}

REMARK
-/-

*/