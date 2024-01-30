/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:40:20 by acomet            #+#    #+#             */
/*   Updated: 2022/10/12 19:50:07 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;
	int				i;

	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	i = n - 1;
	if (ptr == (void *) 0 && ptr2 == (void *) 0)
		return ((void *) 0);
	if (ptr2 >= ptr)
		return (ft_memcpy(ptr, ptr2, n));
	else if (ptr2 < ptr)
	{
		while (i >= 0)
		{
			ptr[i] = ptr2[i];
			i--;
		}
	}
	return (dest);
}
