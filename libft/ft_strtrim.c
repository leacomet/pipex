/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 23:30:03 by acomet            #+#    #+#             */
/*   Updated: 2022/10/16 17:00:21 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_setcount1(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	setcount;

	setcount = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				setcount++;
				break ;
			}
			j++;
		}
		if (set[j] == '\0')
			break ;
		i++;
	}
	return (setcount);
}

static int	ft_setcount2(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	setcount;

	setcount = 0;
	i = ft_strlen(s1) - 1;
	while (s1[i] >= 0)
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				setcount++;
				break ;
			}
			j++;
		}
		if (set[j] == '\0')
			break ;
		i--;
	}
	return (setcount);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		setcount_beg;
	int		setcount_end;
	int		setcount_trim;

	if (s1 == NULL)
		return (NULL);
	setcount_beg = ft_setcount1(s1, set);
	setcount_end = ft_setcount2(s1, set);
	setcount_trim = setcount_beg + setcount_end;
	str = ft_substr(s1, setcount_beg, ft_strlen(s1) - setcount_trim);
	return (str);
}
