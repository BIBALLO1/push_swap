/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:45:23 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/31 15:59:22 by dmoraled         ###   ########.fr       */
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

static void	fill_costs(t_list *a)
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

static void	move_bottom(t_list **lst, t_list *item, char lst_name)
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

// static void	fill_parallel_costs(t_list *a, t_list *b)
// {
// 	int asize = ft_lstsize(a);
// 	int bsize = ft_lstsize(b);
// 	int i = 0;
// 	while (a)
// 	{
// 		int target_rev_i = ft_lstsize(((t_item *)(a->content))->target);
// 		int	base_cost;
// 		if (i < asize / 2 && target_rev_i >= bsize / 2)
// 		{
// 			((t_item *)(a->content))->cost = i;
// 		}
// 		else
// 			base_cost = asize - i;
// 
// 		a = a->next;
// 		++i;
// 	}
// }

void	parallel_move(t_list **a, t_list **b, t_list *cheapest) 
{
	t_list *target = ((t_item *)(cheapest->content))->target;
	int	asize = ft_lstsize(*a);
	int	bsize = ft_lstsize(*b);
	int cheap_r = ft_lstsize(cheapest);
	int target_r = ft_lstsize(target);
	if ((cheap_r <= asize / 2) != (target_r <= bsize / 2))
	{
		// ft_printf("going different ways, cant do nothing\n");
		move_top(a, cheapest, 'a');
		move_bottom(b, target, 'b');
	} else {
		if (cheap_r <= asize / 2)
		{
			while (target_r > 1 && cheap_r > 0)
			{
				rrr(a, b);
				--target_r;
				--cheap_r;
			}
			while (target_r > 1)
			{
				rrs(b, 'b');
				--target_r;
			}
			while (cheap_r > 0)
			{
				rrs(a, 'a');
				--cheap_r;
			}
		}
		else
		{
			while (target_r <= bsize && cheap_r < asize)
			{
				rr(a, b);
				++target_r;
				++cheap_r;
			}
			while (target_r <= bsize)
			{
				rs(b, 'b');
				++target_r;
			}
			while (cheap_r < asize)
			{
				rs(a, 'a');
				++cheap_r;
			}
		}
	}
}

void	sort_complex(t_list **a, t_list **b)
{
	while (ft_lstsize(*b) < 3)
		pb(a, b);
	sort_trivial(b, 'b');
	reverse_trivial(b, 'b');

	// print_stack(*a, *b);
	while (ft_lstsize(*a) > 3)
	{
		fill_targets(*b, *a);
		fill_costs(*b);
		fill_costs(*a);
		t_list *cheapest = cheapest_target(*a);

		// t_list *target = ((t_item *)(cheapest->content))->target;
		parallel_move(a, b, cheapest);
		// move_top(a, cheapest, 'a');
		// move_bottom(b, target, 'b');
		pb(a, b);

		// print_stack(*a, *b);
	}

	sort_trivial(a, 'a');

	while (ft_lstsize(*b) > 0)
	{
		fill_targets(*a, *b);
		// fill_targets(*b, *a);
		fill_costs(*b);
		fill_costs(*a);
		t_list *cheapest = cheapest_target(*b);
		// t_list *cheapest = cheapest_target(*a);

		// ft_printf("cheapest target: %i moves for %i\n", get_combined_cost((t_item *)(cheapest->content)), ((t_item *)(cheapest->content))->index);
		t_list *target = ((t_item *)(cheapest->content))->target;
		move_top(a, target, 'a');
		move_top(b, cheapest, 'b');
		// pb(a, b);
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
