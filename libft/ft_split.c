/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:15:04 by acomet            #+#    #+#             */
/*   Updated: 2022/10/14 13:06:51 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_all(char **grid, int i)
{
	if (grid[i] == NULL)
	{
		while (i > 0)
		{
			i--;
			free(grid[i]);
		}
		free(grid);
	}
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c) && (s[i] != '\0'))
			i++;
		while ((s[i] != c) && (s[i] != '\0'))
		{
			i++;
			if (s[i] == c || s[i] == '\0')
				wordcount++;
		}
	}
	wordcount++;
	return (wordcount);
}

static void	ft_fillgrid(char const *s, char c, int wordcount, char **grid)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	start = 0;
	while (i < wordcount)
	{
		len = 0;
		while ((s[start] == c) && (s[start] != '\0'))
			start++;
		while ((s[start + len] != c) && (s[start + len] != '\0'))
			len++;
		if (len > 0)
		{
			grid[i] = ft_substr(s, start, len);
			ft_free_all(grid, i);
		}
		start += len;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**grid;
	int		wordcount;

	if (s == NULL)
		return (NULL);
	wordcount = ft_wordcount(s, c);
	grid = ft_calloc(wordcount, sizeof(char *));
	if (grid == NULL)
		return (NULL);
	ft_fillgrid(s, c, wordcount, grid);
	return (grid);
}
