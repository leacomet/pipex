/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:25:03 by acomet            #+#    #+#             */
/*   Updated: 2022/11/26 16:16:46 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

static int	ft_printerr_variable(const char *str,
		int i, int final_int, va_list ap)
{
	i++;
	if (str[i] == 'c')
		final_int += ft_printerr_char(va_arg(ap, int));
	if (str[i] == 's')
		final_int += ft_printerr_str(va_arg(ap, char *));
	if (str[i] == 'p')
		final_int += ft_printerr_pointer(va_arg(ap, void *));
	if (str[i] == 'd' || str[i] == 'i')
		final_int += ft_printerr_nbr(va_arg(ap, int));
	if (str[i] == 'u')
		final_int += ft_printerr_unsigned(va_arg(ap, unsigned int));
	if (str[i] == 'x' || str[i] == 'X')
		final_int += ft_printerr_hexa(va_arg(ap, unsigned int), str[i]);
	if (str[i] == '%')
		final_int += ft_printerr_char('%');
	return (final_int);
}

static int	ft_printerr_text(const char *str, int final_int, va_list ap)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			final_int = ft_printerr_variable(str, i, final_int, ap);
			i++;
		}
		else
		{
			write (2, &str[i], 1);
			final_int++;
		}
		i++;
	}
	return (final_int);
}

int	ft_printferr(const char *str, ...)
{
	va_list	ap;
	int		final_int;

	if (str == NULL)
		return (-1);
	final_int = 0;
	va_start(ap, str);
	final_int = ft_printerr_text(str, final_int, ap);
	va_end(ap);
	return (final_int);
}
