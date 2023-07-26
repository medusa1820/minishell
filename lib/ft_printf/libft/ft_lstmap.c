/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:28:53 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 00:31:18 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*space_holder;
	void	*f_ptr;

	if (!f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		f_ptr = f((*lst).content);
		space_holder = ft_lstnew(f_ptr);
		if (space_holder == NULL)
		{
			del(f_ptr);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, space_holder);
		lst = (*lst).next;
	}
	return (new_lst);
}

/*

ft_lstmap:

PARAMETERS
lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.
del: The address of the function used to delete the content 
of a node if needed.

RETURN VALUE
The new list.
NULL if the allocation fails.

DESCRIPTION
Iterates the list ’lst’ and applies the function ’f’ on the 
content of each node. Creates a new list resulting of the 
successive applications of the function ’f’. The ’del’ 
function is used to delete the content of a node if needed.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
-/-

EXPLANATION
of why ft_lstmap failed "francintee --strict" test

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*space_holder;
	void	*f_ptr;

	if (!f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		
// f function can also use malloc, and if it fails to allocate the 
// memory, then f_prt must be also deleted, see line "del(f_ptr)" below
		
		f_ptr = f((*lst).content);
		space_holder = ft_lstnew(f_ptr);
		if (space_holder == NULL)
		{
			del(f_ptr);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, space_holder);
		lst = (*lst).next;
	}
	return (new_lst);
}


REMARK
-/-


*/