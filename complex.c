/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:45:23 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/01 14:40:43 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

static void	fill_targets_down(t_list *to, t_list *from)
{
	t_list	*toit;

	while (from)
	{
		int fv = ((t_item *)(from->content))->index;

		toit = to;
		t_list *target = 0;
		while (toit)
		{
			int tov = ((t_item *)(toit->content))->index;
			if (tov < fv)
			{
				if (!target || 
					((t_item *)(target->content))->index < tov)
					target = toit;
			}
			toit = toit->next;
		}
		if (!target)
		{
			toit = to;
			while (toit)
			{
				int tov = ((t_item *)(toit->content))->index;
				if (!target || tov > ((t_item *)(target->content))->index)
				{
					target = toit;
				}
				toit = toit->next;
			}
		}
		((t_item *)(from->content))->target = target;
		from = from->next;
	}
}

static void	fill_targets(t_list *to, t_list *from)
{
	t_list *fit = from;
	while (fit)
	{
		int fv = ((t_item *)(fit->content))->index;

		t_list *toit = to;
		t_list *target = 0;
		while (toit)
		{
			int tov = ((t_item *)(toit->content))->index;
			if (tov > fv)
			{
				if (!target || 
					((t_item *)(target->content))->index > tov)
					target = toit;
			}
			toit = toit->next;
		}
		if (!target)
		{
			toit = to;
			while (toit)
			{
				int tov = ((t_item *)(toit->content))->index;
				if (!target || tov < ((t_item *)(target->content))->index)
				{
					target = toit;
				}
				toit = toit->next;
			}
		}
		((t_item *)(fit->content))->target = target;
		fit = fit->next;
	}
}

static t_list	*cheapest_target(t_list *b)
{
	t_list	*min;
	int		cost;

	min = 0;
	while (b)
	{
		cost = ((t_item *)(b->content))->cost;
		if (!min || cost < ((t_item *)(min->content))->cost)
			min = b;
		b = b->next;
	}
	return (min);
}

# define MAX(a, b) ((a > b) ? (a) : (b))
# define MIN(a, b) ((a < b) ? (a) : (b))

static int	cheapest_parallel_path(t_list *to, t_list *from, t_list *f, char *fdir, char *tdir)
{
	t_list *target = ((t_item *)(f->content))->target;
	int from_s = ft_lstsize(from);
	int to_s = ft_lstsize(to);
	int min = INT_MAX;
	int fpos = from_s - ft_lstsize(f);
	int tpos = to_s - ft_lstsize(target);
	// both up
	int cost = MIN(fpos, tpos);
	cost += MAX(fpos, tpos) - cost;
	min = cost;
	*tdir = DIRECTION_UP;
	*fdir = DIRECTION_UP;
	// up / down
	cost = fpos + (to_s - tpos);
	if (cost < min)
	{
		min = cost;
		*tdir = DIRECTION_DOWN;
		*fdir = DIRECTION_UP;
	}
	// down / up
	cost = (from_s - fpos) + to_s;
	if (cost < min)
	{
		min = cost;
		*tdir = DIRECTION_UP;
		*fdir = DIRECTION_DOWN;
	}
	// both down
	cost = MIN(from_s - fpos, to_s - tpos);
	cost += MAX(from_s - fpos, to_s - tpos) - cost;
	if (cost < min)
	{
		min = cost;
		*tdir = DIRECTION_DOWN;
		*fdir = DIRECTION_DOWN;
	}
	return (min);
}

static void	parallel_fill_costs(t_list *to, t_list *from)
{
	t_list	*f;
	int		cost;

	f = from;
	while (f)
	{
		cost = cheapest_parallel_path(to, from, f,
				&(((t_item *)(f->content))->direction),
				&(((t_item *)(f->content))->target_dir));
		((t_item *)(f->content))->cost = cost;
		f = f->next;
	}
}

void	parallel_move(t_list **to, t_list **from, t_list *f, t_list *target, char tname, char fname)
{
	char tdir = ((t_item *)(f->content))->target_dir;
	char fdir = ((t_item *)(f->content))->direction;
	int from_s = ft_lstsize(*from);
	int to_s = ft_lstsize(*to);
	int fpos = from_s - ft_lstsize(f);
	int tpos = to_s - ft_lstsize(target);
	if (tdir == fdir)
	{
		if (fdir == DIRECTION_UP)
		{
			while (fpos > 0 && tpos > 0)
			{
				rr(from, to);
				--fpos;
				--tpos;
			}
			while (fpos > 0)
			{
				rs(from, fname);
				--fpos;
			}
			while (tpos > 0)
			{
				rs(to, tname);
				--tpos;
			}
		}
		else
		{
			while (fpos < from_s && tpos < to_s)
			{
				rrr(from, to);
				++fpos;
				++tpos;
			}
			while (fpos < from_s)
			{
				rrs(from, fname);
				++fpos;
			}
			while (tpos < to_s)
			{
				rrs(to, tname);
				++tpos;
			}
		}
	}
	else
	{
		if (fdir == DIRECTION_UP)
		{
			while (fpos > 0)
			{
				rs(from, fname);
				--fpos;
			}
			while (tpos < to_s)
			{
				rrs(to, tname);
				++tpos;
			}
		}
		else
		{
			while (fpos < from_s)
			{
				rrs(from, fname);
				++fpos;
			}
			while (tpos > 0)
			{
				rs(to, tname);
				--tpos;
			}
		}
	}
}

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

void	sort_complex(t_list **a, t_list **b)
{
	t_list	*cheapest;

	pb(a, b);
	while (ft_lstsize(*a) > ft_lstsize(*b))
	{
		fill_targets_down(*b, *a);
		parallel_fill_costs(*b, *a);
		cheapest = cheapest_target(*a);
		t_list *target = ((t_item *)(cheapest->content))->target;

		parallel_move(b, a, cheapest, target, 'b', 'a');
		pb(a, b);
	}
	while (ft_lstsize(*a) > 1)
		pb(a, b);
	while (*b)
	{
		fill_targets(*a, *b);
		parallel_fill_costs(*a, *b);
		cheapest = cheapest_target(*b);
		t_list *target = ((t_item *)(cheapest->content))->target;
		parallel_move(a, b, cheapest, target, 'a', 'b');
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
		fill_targets(*a, *b);
		parallel_fill_costs(*a, *b);
		cheapest = cheapest_target(*b);
		t_list *target = ((t_item *)(cheapest->content))->target;
		parallel_move(a, b, cheapest, target, 'a', 'b');
		pa(a, b);
	}
	scroll_up(a, 'a');
}
