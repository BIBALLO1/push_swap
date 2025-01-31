/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:45:23 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/31 18:10:19 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

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

void	fill_costs(t_list *a)
{
	int asize = ft_lstsize(a);
	int i = 0;
	while (a)
	{
		if (i < asize / 2)
			((t_item *)(a->content))->cost = i;
		else
			((t_item *)(a->content))->cost = asize - i;
		a = a->next;
		++i;
	}
}

static int	get_combined_cost(t_item *item)
{
	return item->cost + ((t_item *)(item->target->content))->cost;
}

static t_list	*cheapest_target(t_list *b)
{
	t_list	*min = 0;
	// int i = 0;
	while (b)
	{
		int cost = get_combined_cost((t_item *)(b->content));
		if (!min || 
			cost < get_combined_cost((t_item *)(min->content)))
			min = b;
		b = b->next;
		// ++i;
	}
	return (min);
}

static void	move_top(t_list **lst, t_list *item, char lst_name)
{
	int lsize = ft_lstsize(*lst);
	int rev_i = ft_lstsize(item);
	if (rev_i <= lsize / 2)
	{
		while (rev_i > 0)
		{
			rrs(lst, lst_name);
			rev_i--;
		}
	}
	else
	{
		while (rev_i < lsize)
		{
			rs(lst, lst_name);
			rev_i++;
		}
	}
}

void	move_bottom(t_list **lst, t_list *item, char lst_name)
{
	int lsize = ft_lstsize(*lst);
	int rev_i = ft_lstsize(item);
	if (rev_i <= lsize / 2)
	{
		while (rev_i > 1)
		{
			rrs(lst, lst_name);
			rev_i--;
		}
	}
	else
	{
		while (rev_i <= lsize)
		{
			rs(lst, lst_name);
			rev_i++;
		}
	}
}

static void	parallel_fill_costs(t_list *to, t_list *from)
{
	int from_s = ft_lstsize(from);
	int to_s = ft_lstsize(to);
	int i = 0;
	while (from)
	{
		t_list	*target = ((t_item *)(from->content))->target;
		int target_rev_i = ft_lstsize(target);
		// int	base_cost;
		if ((i < from_s / 2) == (target_rev_i >= to_s / 2)) // same direction
		{
			if (i < from_s / 2)
			{
				((t_item *)(from->content))->cost = i;
				((t_item *)(from->content))->direction = DIRECTION_UP;
				((t_item *)(target->content))->cost = to_s - target_rev_i;
				((t_item *)(target->content))->direction = DIRECTION_UP;
			}
			else 
			{
				((t_item *)(from->content))->cost = from_s - i;
				((t_item *)(from->content))->direction = DIRECTION_DOWN;
				((t_item *)(target->content))->cost = target_rev_i;
				((t_item *)(target->content))->direction = DIRECTION_DOWN;
			}
		}
		else
		{
			if (i < from_s / 2)
			{
				((t_item *)(from->content))->cost = i;
				((t_item *)(from->content))->direction = DIRECTION_UP;
				((t_item *)(target->content))->cost = target_rev_i;
				((t_item *)(target->content))->direction = DIRECTION_DOWN;
			}
			else 
			{
				((t_item *)(from->content))->cost = from_s - i;
				((t_item *)(from->content))->direction = DIRECTION_DOWN;
				((t_item *)(target->content))->cost = to_s - target_rev_i;
				((t_item *)(target->content))->direction = DIRECTION_UP;
			}
		}

		// ft_printf("assigned from %i (cost %i, dir %i) to %i (cost %i, dir %i)\n",
		// 	((t_item *)(from->content))->index,
		// 	((t_item *)(from->content))->cost,
		// 	((t_item *)(from->content))->direction,
		// 	((t_item *)(target->content))->index,
		// 	((t_item *)(target->content))->cost,
		// 	((t_item *)(target->content))->direction
		// );

		from = from->next;
		++i;
	}
}

void	parallel_move(t_list **to, t_list **from, t_list *cheapest, t_list *target) 
{
	int	from_s = ft_lstsize(*from);
	int	to_s = ft_lstsize(*to);
	char cheap_dir = ((t_item *)(cheapest->content))->direction;
	char target_dir = ((t_item *)(target->content))->direction;
	int cheap_r = ft_lstsize(cheapest);
	int target_r = ft_lstsize(target);
	// ft_printf("dirs: %i %i \n", cheap_dir, target_dir);
	if (cheap_dir != target_dir)
	{
		// ft_printf("going different ways, cant do nothing\n");
		move_top(to, target, 'a');
		move_top(from, cheapest, 'b');
		// move_bottom(from, target, 'b');
	} else {
		if (cheap_dir == DIRECTION_DOWN)
		{
			while (target_r > 0 && cheap_r > 0)
			{
				rrr(to, from);
				--target_r;
				--cheap_r;
			}
			while (target_r > 0)
			{
				rrs(to, 'a');
				--target_r;
			}
			while (cheap_r > 0)
			{
				rrs(from, 'b');
				--cheap_r;
			}
		}
		else
		{
			while (target_r < to_s && cheap_r < from_s)
			{
				rr(to, from);
				++target_r;
				++cheap_r;
			}
			while (target_r < to_s)
			{
				rs(to, 'a');
				++target_r;
			}
			while (cheap_r < from_s)
			{
				rs(from, 'b');
				++cheap_r;
			}
		}
	}
}

void	sort_complex(t_list **a, t_list **b)
{
	while (ft_lstsize(*a) > 3)
		pb(a, b);
	sort_trivial(a, 'a');
	// reverse_trivial(b, 'b');

	// print_stack(*a, *b);
	while (*b)
	{
		fill_targets(*a, *b);
		parallel_fill_costs(*a, *b);
		// ft_printf("got here\n");
		// fill_costs(*b);
		// fill_costs(*a);
		t_list *cheapest = cheapest_target(*b);
		t_list *target = ((t_item *)(cheapest->content))->target;
		// ft_printf("selected: %i -> %i (%i|%i)\n",
		// 	((t_item *)(cheapest->content))->index,
		// 	((t_item *)(target->content))->index,
		// 	((t_item *)(cheapest->content))->direction,
		// 	((t_item *)(target->content))->direction
		// );

		// t_list *target = ((t_item *)(cheapest->content))->target;
		parallel_move(a, b, cheapest, target);
		pa(a, b);

		// print_stack(*a, *b);
	}

	int i = 0;
	t_list *ait = *a;
	while (ait)
	{
		if (((t_item *)(ait->content))->index == 0)
			break;
		ait = ait->next;
		i++;
	}
	move_top(a, ait, 'a');
}

// void	sort_complex(t_list **a, t_list **b)
// {
// 	while (ft_lstsize(*b) < 3)
// 		pb(a, b);
// 	sort_trivial(b, 'b');
// 	reverse_trivial(b, 'b');
// 
// 	// print_stack(*a, *b);
// 	while (ft_lstsize(*a) > 3)
// 	{
// 		fill_targets(*b, *a);
// 		parallel_fill_costs(*a, *b);
// 		// fill_costs(*b);
// 		// fill_costs(*a);
// 		t_list *cheapest = cheapest_target(*a);
// 
// 		// t_list *target = ((t_item *)(cheapest->content))->target;
// 		parallel_move(a, b, cheapest);
// 		// move_top(a, cheapest, 'a');
// 		// move_bottom(b, target, 'b');
// 		pb(a, b);
// 
// 		// print_stack(*a, *b);
// 	}
// 
// 	sort_trivial(a, 'a');
// 
// 	while (ft_lstsize(*b) > 0)
// 	{
// 		fill_targets(*a, *b);
// 		// fill_targets(*b, *a);
// 		fill_costs(*b);
// 		fill_costs(*a);
// 		t_list *cheapest = cheapest_target(*b);
// 		// t_list *cheapest = cheapest_target(*a);
// 
// 		// ft_printf("cheapest target: %i moves for %i\n", get_combined_cost((t_item *)(cheapest->content)), ((t_item *)(cheapest->content))->index);
// 		t_list *target = ((t_item *)(cheapest->content))->target;
// 		move_top(a, target, 'a');
// 		move_top(b, cheapest, 'b');
// 		// pb(a, b);
// 		pa(a, b);
// 
// 		// print_stack(*a, *b);
// 	}
// 
// 	int i = 0;
// 	t_list *ait = *a;
// 	while (ait)
// 	{
// 		if (((t_item *)(ait->content))->index == 0)
// 			break;
// 		ait = ait->next;
// 		i++;
// 	}
// 	move_top(a, ait, 'a');
// }
