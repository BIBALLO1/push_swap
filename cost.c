/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:08:38 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/02 21:23:31 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

static void	test_cost_uu(int tsize, int fsize, t_list *f, int *min)
{
	int	cost;
	int	tpos;
	int	fpos;

	fpos = fsize - ft_lstsize(f);
	tpos = tsize - ft_lstsize(((t_item *)(f->content))->target);
	cost = ft_min(fpos, tpos);
	cost += ft_max(fpos, tpos) - cost;
	if (cost < *min)
	{
		*min = cost;
		((t_item *)(f->content))->target_dir = DIRECTION_UP;
		((t_item *)(f->content))->direction = DIRECTION_UP;
	}
}

static void	test_cost_ud(int tsize, int fsize, t_list *f, int *min)
{
	int	cost;
	int	fpos;

	(void)tsize;
	fpos = fsize - ft_lstsize(f);
	cost = fpos + ft_lstsize(((t_item *)(f->content))->target);
	if (cost < *min)
	{
		*min = cost;
		((t_item *)(f->content))->target_dir = DIRECTION_DOWN;
		((t_item *)(f->content))->direction = DIRECTION_UP;
	}
}

static void	test_cost_du(int tsize, int fsize, t_list *f, int *min)
{
	int	cost;

	(void)fsize;
	cost = ft_lstsize(f)
		+ (tsize - ft_lstsize(((t_item *)(f->content))->target));
	if (cost < *min)
	{
		*min = cost;
		((t_item *)(f->content))->target_dir = DIRECTION_UP;
		((t_item *)(f->content))->direction = DIRECTION_DOWN;
	}
}

static void	test_cost_dd(int tsize, int fsize, t_list *f, int *min)
{
	int		cost;
	int		fs;
	int		ts;

	(void)tsize;
	(void)fsize;
	fs = ft_lstsize(f);
	ts = ft_lstsize(((t_item *)(f->content))->target);
	cost = ft_min(fs, ts);
	cost += ft_max(fs, ts) - cost;
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
	int		tsize;
	int		fsize;

	f = from;
	while (f)
	{
		min = INT_MAX;
		tsize = ft_lstsize(to);
		fsize = ft_lstsize(from);
		test_cost_uu(tsize, fsize, f, &min);
		test_cost_ud(tsize, fsize, f, &min);
		test_cost_du(tsize, fsize, f, &min);
		test_cost_dd(tsize, fsize, f, &min);
		((t_item *)(f->content))->cost = min;
		f = f->next;
	}
}
