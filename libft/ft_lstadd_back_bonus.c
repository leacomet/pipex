/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:32:57 by acomet            #+#    #+#             */
/*   Updated: 2023/04/14 13:30:55 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	t_list	*temp;

	if (*lst == NULL)
	{
		*lst = new_lst;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new_lst;
}
