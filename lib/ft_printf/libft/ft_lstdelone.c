/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:57:45 by musenov           #+#    #+#             */
/*   Updated: 2022/12/08 18:35:03 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del((*lst).content);
	free(lst);
}

/*

ft_lstdelone:

PARAMETERS
lst: The node to free.
del: The address of the function used to delete the content

RETURN VALUE
None

DESCRIPTION
Takes as a parameter a node and frees the memory of the node’s content 
using the function ’del’ given as a parameter and free the node. 
The memory of ’next’ must not be freed.

QUESTIONS
why do we have to free the lst???
if it is freed, then we cant access lst->next!

ANSWER
Read the description

COMPARE
-/-

ALTERNATIVE SOLUTION
-/-

EXPLANATION
-/-

REMARK
lst points exactly to that node whose content is deleted and the pointer lst
itslef will be freed

*/