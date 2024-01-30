/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:13:35 by acomet            #+#    #+#             */
/*   Updated: 2022/10/12 19:44:32 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennbr(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_inttochar(int n, int len, char *str)
{
	if (n == -2147483648)
	{
		str[len] = '8';
		n /= 10;
		len--;
	}
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (len >= 0 && str[len] != '-')
	{
		str[len] = n % 10 + 48;
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_lennbr(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	len--;
	ft_inttochar(n, len, str);
	return (str);
}
