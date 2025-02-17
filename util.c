/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:16:36 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/17 13:14:14 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

int	lst_item_less(void *a, void *b)
{
	return (((t_item *)(a))->index < ((t_item *)(b))->index);
}

int	lst_item_more(void *a, void *b)
{
	return (((t_item *)(a))->index > ((t_item *)(b))->index);
}

t_list	*lst_min_value(t_list *lst, int threshold)
{
	long	min;
	t_list	*min_node;
	t_item	*item;

	min = (long)INT_MAX + 1;
	min_node = 0;
	while (lst)
	{
		item = (t_item *)(lst->content);
		if (item->value == min)
		{
			item->index = -1;
			return (lst);
		}
		if (item->value < min && item->value > threshold)
		{
			min = item->value;
			min_node = lst;
		}
		lst = lst->next;
	}
	return (min_node);
}

int	is_sorted(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (((t_item *)(lst->content))->index != i)
			return (0);
		lst = lst->next;
		++i;
	}
	return (1);
}
