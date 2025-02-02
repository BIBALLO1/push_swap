/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:32:51 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/02 18:17:18 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	*get_target(t_list *to, t_list *item, int (*l)(void *, void *))
{
	t_list	*toit;
	t_list	*target;

	toit = to;
	target = 0;
	while (toit)
	{
		if (l(toit->content, item->content)
			&& (!target || l(target->content, toit->content)))
			target = toit;
		toit = toit->next;
	}
	if (!target)
		target = ft_lstmax(to, l);
	return (target);
}

void	fill_targets(t_list *to, t_list *from, int (*l)(void *, void *))
{
	while (from)
	{
		((t_item *)(from->content))->target = get_target(to, from, l);
		from = from->next;
	}
}

t_list	*cheapest_target(t_list *b, t_list *allowed_start, int allowed_size)
{
	t_list	*min;
	int		cost;

	min = 0;
	while (b && b != allowed_start)
	{
		cost = ((t_item *)(b->content))->cost;
		if (!min || cost < ((t_item *)(min->content))->cost)
			min = b;
		b = b->next;
	}
	if (b == allowed_start)
		while (b && (allowed_size--))
			b = b->next;
	while (b)
	{
		cost = ((t_item *)(b->content))->cost;
		if (!min || cost < ((t_item *)(min->content))->cost)
			min = b;
		b = b->next;
	}
	return (min);
}
