/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xXp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:10:37 by acomet            #+#    #+#             */
/*   Updated: 2022/11/23 21:10:35 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

int	ft_printerr_hexa(unsigned long nbr, char c)
{
	int	i;

	i = 0;
	if (nbr >= 16)
		i += ft_printerr_hexa(nbr / 16, c);
	if (c == 'x')
		i += ft_printerr_char("0123456789abcdef"[nbr % 16]);
	else
		i += ft_printerr_char("0123456789ABCDEF"[nbr % 16]);
	return (i);
}

int	ft_printerr_pointer(void *ptr)
{
	unsigned long	nbr;
	int				i;

	nbr = (unsigned long)ptr;
	i = 0;
	if (ptr == NULL)
		return (ft_printerr_str("(nil)"));
	i += ft_printerr_str("0x");
	i += ft_printerr_hexa(nbr, 'x');
	return (i);
}
