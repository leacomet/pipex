/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:17:39 by acomet            #+#    #+#             */
/*   Updated: 2022/10/03 18:35:29 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	if ((nmemb > 2147483647) || size > 2147483647
		|| (nmemb * size > 2147483647))
		return ((void *) 0);
	str = malloc(nmemb * size);
	if (str == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
