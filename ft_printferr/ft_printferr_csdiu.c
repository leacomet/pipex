/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_csdiu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:10:19 by acomet            #+#    #+#             */
/*   Updated: 2022/11/23 21:10:27 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

int	ft_printerr_char(const char c)
{
	write(2, &c, 1);
	return (1);
}

int	ft_printerr_str(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(2, "(null)", 6);
		return (6);
	}
	while (str[i])
		write(2, &str[i++], 1);
	return (i);
}

int	ft_printerr_nbr(int nbr)
{
	int		i;

	i = 0;
	if (nbr == -2147483648)
		return (ft_printerr_str("-2147483648"));
	while (nbr < 0)
	{
		i += ft_printerr_char('-');
		nbr *= -1;
	}
	if (nbr >= 10)
		i += ft_printerr_nbr(nbr / 10);
	i += ft_printerr_char("0123456789"[nbr % 10]);
	return (i);
}

int	ft_printerr_unsigned(unsigned int nbr)
{
	int		i;

	i = 0;
	if (nbr >= 10)
		i += ft_printerr_nbr(nbr / 10);
	i += ft_printerr_char("0123456789"[nbr % 10]);
	return (i);
}
