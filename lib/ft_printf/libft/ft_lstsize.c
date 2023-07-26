/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:24:21 by musenov           #+#    #+#             */
/*   Updated: 2022/12/07 18:05:52 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = (*lst).next;
		size++;
	}
	return (size);
}

/*

ft_lstsize:

PARAMETERS
lst: The beginning of the list.

RETURN VALUE
The length of the list

DESCRIPTION
Counts the number of nodes in a list.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = (*lst).next;
		size++;
	}
	return (size);
}

EXPLANATION
-/-

REMARK
-/-


*/