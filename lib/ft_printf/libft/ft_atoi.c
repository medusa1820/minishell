/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:13:37 by musenov           #+#    #+#             */
/*   Updated: 2022/12/06 18:31:48 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	output;

	i = 0;
	sign = 1;
	while ((*(str + i) >= 9 && *(str + i) <= 13) || *(str + i) == ' ')
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	output = 0;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		output = output * 10 + (*(str + i) - '0');
		if (output < 0 && sign == 1)
			return (-1);
		if (output < 0 && sign == -1 && output != -2147483648)
			return (0);
		i++;
	}
	return (output * sign);
}

/*

ft_atoi:

PARAMETERS
-/-

RETURN VALUE
-/-

DESCRIPTION
The atoi() function converts the initial portion of the string 
pointed to by str to int representation.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
-/-

EXPLANATION

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	output;

	i = 0;
	sign = 1;
	while ((*(str + i) >= 9 && *(str + i) <= 13) || *(str + i) == ' ')
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	output = 0;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		output = output * 10 + (*(str + i) - '0');

for big positive number, like "99999999999999999999999999". It will not
overflow several times and be negative then positive then negative and 
so on. It will overflow only once and the check below returns "-1"
		if (output < 0 && sign == 1)
			return (-1);

for big negative number, like "-99999999999999999999999999". It will not
overflow several times and be positive then negative then positive and 
so on. It will overflow only once and the check below returns "0".
Though we have an exlusion here. We want to let it go "2147483648".
Because when we want to convert "-2147483648" to integer we remove minus,
and there is no positive integer for "2147483648", it can only be max. 
"2147483647". Therefore at last iteration "2147483648" will oveflow to 
"-2147483648".

		if (output < 0 && sign == -1 && output != -2147483648)
			return (0);
		i++;
	}

Then we multiply "-2147483648" to sign "-1". See whats 
inside "return" operator. Result will be "2147483648" and will again 
overflow to "-2147483648". And that is the answer we want to have. 
	return (output * sign);
}

REMARK
-/-


*/

/*
int	main(void)
{
	char	str1[] = "99999999999999999999999999";
	char	str2[] = "-99999999999999999999999999";
	char	str3[] = "-2147483648";

	printf("integer for 99999999999999999999999999: %d\n", atoi(str1));
	printf("integer for -99999999999999999999999999: %d\n", atoi(str2));
	printf("integer for -2147483648: %d\n", atoi(str3));
	printf("integer for 99999999999999999999999999: %d\n", ft_atoi(str1));
	printf("integer for -99999999999999999999999999: %d\n", ft_atoi(str2));
	printf("integer for -2147483648: %d\n", ft_atoi(str3));
	return (0);
}

-2147483648 

*/