/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:27:42 by acomet            #+#    #+#             */
/*   Updated: 2022/10/12 19:09:49 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	l_dest;
	size_t	l_src;

	i = 0;
	l_src = ft_strlen(src);
	if (size == 0)
		return (l_src);
	l_dest = ft_strlen(dst);
	if (l_dest >= size)
		return (size + l_src);
	while (src[i] != '\0' && l_dest + i < size)
	{
		dst[l_dest + i] = src[i];
		i++;
	}
	if ((size <= l_dest + l_src))
		dst[l_dest + i - 1] = '\0';
	else
		dst[l_dest + i] = '\0';
	return (l_dest + l_src);
}
