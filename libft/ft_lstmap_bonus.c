/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:33:58 by acomet            #+#    #+#             */
/*   Updated: 2022/10/12 17:13:48 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*start;
	t_list	*temp;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (new == NULL)
		return (NULL);
	start = new;
	temp = lst->next;
	while (temp != NULL)
	{
		new->next = ft_lstnew(f(temp->content));
		if (new->next == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		temp = temp->next;
		new = new->next;
	}
	return (start);
}
