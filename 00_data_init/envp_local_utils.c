/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_local_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:35:25 by musenov           #+#    #+#             */
/*   Updated: 2023/09/28 15:36:05 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp_local(char **array)
{
	int		i;

	i = 0;
	if (!array)
		printf("Array is NULL\n");
	else
	{
		while (array[i])
		{
			printf("%s\n", array[i]);
			i++;
		}
	}
}

void	free_envp_local(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
