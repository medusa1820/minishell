/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:34:05 by musenov           #+#    #+#             */
/*   Updated: 2022/12/08 15:24:51 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c);
static int	ft_word_len(char const *s, char c, int i);
char		**ft_splits(char const *s, char c, int *word_count, char **strings);

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**strings;

	if (!s)
		return (0);
	word_count = ft_word_count(s, c);
	strings = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!strings)
		return (0);
	return (ft_splits(s, c, &word_count, strings));
}

char	**ft_splits(char const *s, char c, int *word_count, char **strings)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (i < *word_count)
	{
		while (*(s + j) == c)
			j++;
		word_len = ft_word_len(s, c, j);
		*(strings + i) = ft_substr(s, j, word_len);
		if (!*(strings + i))
		{
			while (i-- > 0)
				free(*(strings + i));
			free(strings);
			return (0);
		}
		j = j + word_len;
		i++;
	}
	*(strings + i) = 0;
	return (strings);
}

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s && *(s + i) != '\0')
	{
		if (*(s + i) == c)
			i++;
		else
		{
			word_count++;
			while (*(s + i) != '\0' && *(s + i) != c)
				i++;
		}
	}
	return (word_count);
}

static int	ft_word_len(char const *s, char c, int j)
{
	int	start;

	start = j;
	while (*(s + j) != 0 && *(s + j) != c)
		j++;
	return (j - start);
}

/*

ft_split:

PARAMETERS
s: The string to be split.
c: The delimiter character.

RETURN VALUE
The array of new strings resulting from the split. NULL if 
the allocation fails.

DESCRIPTION
Allocates (with malloc(3)) and returns an array of strings obtained by 
splitting ’s’ using the character ’c’ as a delimiter. The array must 
end with a NULL pointer.

QUESTIONS
-/-

ANSWER
-/-

COMPARE
-/-

ALTERNATIVE SOLUTION
-/-

EXPLANATION

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**strings;

	if (!s)
		return (0);
	word_count = ft_word_count(s, c);
	strings = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!strings)
		return (0);
	return (ft_splits(s, c, &word_count, strings));
}


// this function must return a NULL-pointer if ft_substr fails as 
// we have in it a line of code which returns '0' [return (0)]

char	**ft_splits(char const *s, char c, int *word_count, char **strings)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (i < *word_count)
	{
		while (*(s + j) == c)
			j++;
		word_len = ft_word_len(s, c, j);
		*(strings + i) = ft_substr(s, j, word_len);
		if (!*(strings + i))

// There is a malloc() functin in ft_substr(). If substr function fails
// we must free the variable strings, first by freeing branches then by freeing
// the variable strings itself
		{
			while (i-- > 0)
				free(*(strings + i));
			free(strings);
			return (0);
		}
		j = j + word_len;
		i++;
	}

// Works only with NULL or 0 and not '\0', why?
	*(strings + i) = 0;
	return (strings);
}

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s && *(s + i) != '\0')
	{
		if (*(s + i) == c)
			i++;
		else
		{
			word_count++;
			while (*(s + i) != '\0' && *(s + i) != c)
				i++;
		}
	}
	return (word_count);
}

static int	ft_word_len(char const *s, char c, int j)
{
	int	start;

	start = j;
	while (*(s + j) != 0 && *(s + j) != c)
		j++;
	return (j - start);
}


REMARK
-/-

REMARK
-/-


*/