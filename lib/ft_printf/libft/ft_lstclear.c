/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:58:36 by musenov           #+#    #+#             */
/*   Updated: 2022/12/08 18:43:53 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*buffer;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		buffer = (**lst).next;
		del((**lst).content);
		free(*lst);
		*lst = buffer;
	}
	*lst = NULL;
}

/*

ft_lstclear:

PARAMETERS
lst: The address of a pointer to a node.
del: The address of the function used to delete the content of the node.

RETURN VALUE
None

DESCRIPTION
Deletes and frees the given node and every successor of that node, 
using the function ’del’ and free(3). Finally, the pointer to the 
list must be set to NULL.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-


ALTERNATIVE SOLUTION
-/-

EXPLANATION
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*buffer;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		buffer = (**lst).next;
		del((**lst).content);
		free(*lst);

// '*lst' goes back to while loops condition and it will iterate this until
// all nodes are freed and contents are deleted 
		*lst = buffer;
	}
	*lst = NULL;
}

REMARK
This part in code above can be replaced by ft_lstdelone!

	del((**lst).content);
	free(lst);

*/