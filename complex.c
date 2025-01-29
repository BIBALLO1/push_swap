/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:45:23 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/29 11:22:45 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

static int	lst_at(t_list *a, int idx)
{
	return (((t_item *)(ft_lstidx(a, idx)->content))->index);
}

static int	*get_targets(t_list *a, t_list *b)
{
	int bsize = ft_lstsize(b);
	int *targets = malloc(sizeof(int) * bsize);
	int i = 0;
	t_list *bit = b;
	while (bit)
	{
		int bv = ((t_item *)(bit->content))->index;

		t_list *ait = a;
		int nearest = INT_MAX;
		int j = 0;
		int jmin = 0;
		while (ait)
		{
			int av = ((t_item *)(ait->content))->index;
			if (av > bv && av < nearest)
			{
				nearest = av;
				jmin = j;
			}
			ait = ait->next;
			++j;
		}
		if (nearest == INT_MAX)
		{
			j = 0;
			ait = a;
			while (ait)
			{
				int v = ((t_item *)(ait->content))->index;
				if (v < nearest)
				{
					nearest = v;
					jmin = j;
				}
				ait = ait->next;
				++j;
			}
		}
		// ((t_item *)(bit->content))->target = jmin;
		targets[i] = jmin;

		bit = bit->next;
		++i;
	}
	return (targets);
}

void	sort_complex(t_list **a, t_list **b)
{
	while (ft_lstsize(*a) > 3)
		pb(a, b);
	sort_trivial(a);

	int bsize = ft_lstsize(*b);
	int *targets = get_targets(*a, *b);
	int mincost = INT_MAX;
	int mincosti = -1;
	int i = 0;
	while (i < bsize)
	{
		int cost;
		if (targets[i] > ft_lstsize(*a) / 2)
			cost = ft_lstsize(*a) - targets[i];
		else
			cost = targets[i];
		if (cost < mincost)
		{
			mincost = cost;
			mincosti = i;
		}
		ft_printf("min for %i: %i, cost: %i\n", lst_at(*b, i), lst_at(*a, targets[i]), cost);
		++i;
	}
	ft_printf("cheapest: %i to %i\n", lst_at(*b, mincosti), lst_at(*a, targets[mincosti]));
	int target = targets[mincosti];
	free(targets);
	if (target > ft_lstsize(*a) / 2)
	{
		while (target < ft_lstsize(*a))
		{
			target++;
			rrs(a, 'a');
		}
	}
	else
	{
		while (target > 0)
		{
			target--;
			rs(a, 'a');
		}
	}
	pa(a, b);
}
