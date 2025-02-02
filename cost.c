/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:08:38 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/02 18:25:12 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	test_cost_uu(t_list *to, t_list *from, t_list *f, int *min)
{
	int	cost;
	int	tpos;
	int	fpos;

	fpos = ft_lstsize(from) - ft_lstsize(f);
	tpos = ft_lstsize(to) - ft_lstsize(((t_item *)(f->content))->target);
	cost = ft_min(fpos, tpos);
	cost += ft_max(fpos, tpos) - cost;
	if (cost < *min)
	{
		*min = cost;
		((t_item *)(f->content))->target_dir = DIRECTION_UP;
		((t_item *)(f->content))->direction = DIRECTION_UP;
	}
}

static void	test_cost_ud(t_list *to, t_list *from, t_list *f, int *min)
{
	int	cost;
	int	fpos;

	(void)to;
	fpos = ft_lstsize(from) - ft_lstsize(f);
	cost = fpos + ft_lstsize(((t_item *)(f->content))->target);
	if (cost < *min)
	{
		*min = cost;
		((t_item *)(f->content))->target_dir = DIRECTION_DOWN;
		((t_item *)(f->content))->direction = DIRECTION_UP;
	}
}

static void	test_cost_du(t_list *to, t_list *from, t_list *f, int *min)
{
	int	cost;

	(void)from;
	cost = ft_lstsize(f)
		+ (ft_lstsize(to) - ft_lstsize(((t_item *)(f->content))->target));
	if (cost < *min)
	{
		*min = cost;
		((t_item *)(f->content))->target_dir = DIRECTION_UP;
		((t_item *)(f->content))->direction = DIRECTION_DOWN;
	}
}

static void	test_cost_dd(t_list *to, t_list *from, t_list *f, int *min)
{
	int		cost;
	t_list	*target;

	(void)to;
	(void)from;
	target = ((t_item *)(f->content))->target;
	cost = ft_min(ft_lstsize(f), ft_lstsize(target));
	cost += ft_max(ft_lstsize(f), ft_lstsize(target)) - cost;
	if (cost < *min)
	{
		*min = cost;
		((t_item *)(f->content))->target_dir = DIRECTION_DOWN;
		((t_item *)(f->content))->direction = DIRECTION_DOWN;
	}
}

void	fill_costs(t_list *to, t_list *from)
{
	t_list	*f;
	int		min;

	f = from;
	while (f)
	{
		min = INT_MAX;
		test_cost_uu(to, from, f, &min);
		test_cost_ud(to, from, f, &min);
		test_cost_du(to, from, f, &min);
		test_cost_dd(to, from, f, &min);
		((t_item *)(f->content))->cost = min;
		f = f->next;
	}
}
