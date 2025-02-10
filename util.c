/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:16:36 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/10 16:31:23 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	lst_item_less(void *a, void *b)
{
	return (((t_item *)(a))->index < ((t_item *)(b))->index);
}

int	lst_item_more(void *a, void *b)
{
	return (((t_item *)(a))->index > ((t_item *)(b))->index);
}

int	lst_min_value(t_list *lst, int threshold)
{
	long	min;
	int		min_idx;
	t_item	*item;
	int		curr_idx;

	min = (long)INT_MAX + 1;
	min_idx = -1;
	curr_idx = 0;
	while (lst)
	{
		item = (t_item *)(lst->content);
		if (item->value == min)
			return (-2);
		if (item->value < min && item->value > threshold)
		{
			min = item->value;
			min_idx = curr_idx;
		}
		lst = lst->next;
		++curr_idx;
	}
	return (min_idx);
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
