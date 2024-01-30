/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:54:58 by acomet            #+#    #+#             */
/*   Updated: 2022/11/23 20:33:55 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_print_char(const char c);
int	ft_print_str(const char *str);
int	ft_print_pointer(void *ptr);
int	ft_print_nbr(int nbr);
int	ft_print_unsigned(unsigned int nbr);
int	ft_print_hexa(unsigned long nbr, char c);

#endif
