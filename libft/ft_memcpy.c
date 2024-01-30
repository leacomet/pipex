/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:37:02 by acomet            #+#    #+#             */
/*   Updated: 2022/10/08 14:48:02 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;

	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	if (ptr == NULL && ptr2 == NULL)
		return ((void *) 0);
	while (n > 0)
	{
		*ptr = *ptr2;
		ptr++;
		ptr2++;
		n--;
	}
	return (dest);
}
