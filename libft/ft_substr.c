/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:14:56 by acomet            #+#    #+#             */
/*   Updated: 2022/10/17 16:06:58 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_s_cpy(char const *s, char *str, unsigned int start, size_t i)
{
	str[i] = s[start + i];
	i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s) || len == 0)
	{
		str = malloc(1);
		if (str == NULL)
			return (NULL);
		*str = '\0';
		return (str);
	}
	if (ft_strlen(s + start) > len)
		str = malloc(sizeof(char) * len + 1);
	else
		str = malloc(sizeof(char) * ft_strlen(s + start) + 1);
	if (str == NULL)
		return (NULL);
	while (i <= len - 1 && s[start + i] != '\0')
		i = ft_s_cpy(s, str, start, i);
	str[i] = '\0';
	return (str);
}
