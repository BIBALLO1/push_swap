/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:45:23 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/02 18:21:08 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	scroll_up(t_list **l, char name)
{
	t_list	*ait;
	int		i;

	ait = *l;
	i = 0;
	while (ait)
	{
		if (((t_item *)(ait->content))->index == 0)
			break ;
		ait = ait->next;
		++i;
	}
	if (i < ft_lstsize(*l) / 2)
	{
		while ((--i) >= 0)
			rs(l, name);
	}
	else
	{
		while ((++i) <= ft_lstsize(*l))
			rrs(l, name);
	}
}

static int	eql_idx(void *c, void *idx)
{
	return (((t_item *)(c))->index == *(int *)idx);
}

static void	push_half(t_list **a, t_list **b)
{
	t_list	*cheapest;

	pb(a, b);
	while (ft_lstsize(*a) > ft_lstsize(*b))
	{
		fill_targets(*b, *a, lst_item_less);
		fill_costs(*b, *a);
		cheapest = cheapest_target(*a, 0, ft_lstsize(*a));
		parallel_move((t_list **[]){a, b}, cheapest, 'b', 'a');
		pb(a, b);
	}
}

void	sort_complex(t_list **a, t_list **b)
{
	t_list	*cheapest;
	int		allowed_size;
	t_list	*allowed_start;

	push_half(a, b);
	allowed_size = ft_lstsize(*b);
	allowed_start = ft_lstfind(
			*b, &((t_item *)((*b)->content))->index, eql_idx);
	while (ft_lstsize(*a) > 1)
		pb(a, b);
	while (*b)
	{
		fill_targets(*a, *b, lst_item_more);
		fill_costs(*a, *b);
		cheapest = cheapest_target(*b, allowed_start, allowed_size);
		if (!cheapest)
		{
			allowed_start = 0;
			cheapest = cheapest_target(*b, allowed_start, allowed_size);
		}
		parallel_move((t_list **[]){b, a}, cheapest, 'a', 'b');
		pa(a, b);
	}
	scroll_up(a, 'a');
}

void	sort_small(t_list **a, t_list **b)
{
	t_list	*cheapest;

	while (ft_lstsize(*a) > 3)
		pb(a, b);
	sort_trivial(a, 'a');
	while (*b)
	{
		fill_targets(*a, *b, lst_item_more);
		fill_costs(*a, *b);
		cheapest = cheapest_target(*b, 0, ft_lstsize(*b));
		parallel_move((t_list **[]){b, a}, cheapest, 'a', 'b');
		pa(a, b);
	}
	scroll_up(a, 'a');
}
