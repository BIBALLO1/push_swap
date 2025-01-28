/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/29 00:48:19 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

void	print_stack(t_list *a, t_list *b)
{
	ft_printf("---\n");
	while (a || b)
	{
		if (a)
		{
			ft_printf("%i ", ((t_item *)a->content)->index);
			a = a->next;
		}
		else
		{
			ft_printf("  ");
		}
		if (b)
		{
			ft_printf("%i ", ((t_item *)b->content)->index);
			b = b->next;
		}
		ft_printf("\n");
	}
}

int	lst_check_radix_val(t_list *lst, int dig, int val)
{
	int	item_dig;
	
	while (lst) {
		item_dig = (((t_item *)lst->content)->index & (1 << dig)) != 0;
		if (item_dig != val)
			return (0);
		lst = lst->next;
	}
	return (1);
}

static int	a_mag_l(int a, int b)
{
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;
	return (a < b);
}

void	sort_portion(t_list **a, t_list **b, int from, int to)
{
	// int	med;
	int	it;
	int	asize;

	it = 0;
	asize = ft_lstsize(*a);
	int skipped = 0;
	// med = asize / 2;
	int skip_mode = 0;
	while (it < asize && skip_mode != 1)
	{
		int v = ((t_item *)((*a)->content))->index;
		if (v < from) // if worth it, skip already sorted
		{
			if (skipped < asize / 2)
				skip_mode = 1;
			else
				skip_mode = 2;
		}
		if (v >= from && v < to)
		{
			pb(a, b);
		}
		else 
		{
			rs(a, 'a');
			++skipped;
		}
		++it;
		// print_stack(*a, *b);
	}
	while (skipped > 0 && skip_mode == 1)
	{
		rrs(a, 'a');
		--skipped;
	}

	// reinsert
	int pushed_back = 0;
	while (ft_lstsize(*b) > 0)
	{
		t_list *bit = *b;
		int maxv = 0;
		int minv = asize;
		while (bit)
		{
			int curr = ((t_item *)(bit->content))->index;
			if (curr < minv)
				minv = curr;
			if (curr > maxv)
				maxv = curr;
			bit = bit->next;
		}

		int max = 0;
		int min = 0;
		bit = *b;
		int i = 0;
		int bsize = ft_lstsize(*b);
		while (bit && (max == 0 || min == 0))
		{
			if (((t_item *)(bit->content))->index == maxv)
			{
				int dst_up = i + 1; // one for the push
				int dst_down = bsize - i + 1;
				if (dst_up < dst_down)
					max = dst_up;
				else
					max = -dst_down;
				// ft_printf("max: %i\n", max);
				// maxi = i;
			}
			if (((t_item *)(bit->content))->index == minv)
			{
				int dst_up = i + 2; // one for push, one for rot in a
				int dst_down = bsize - i + 2;
				// ft_printf("min is up: %i, down: %i\n", dst_up, dst_down);
				if (dst_up < dst_down)
					min = dst_up;
				else
					min = -dst_down;
				// ft_printf("min: %i\n", min);
				// mini = i;
			}
			bit = bit->next;
			++i;
		}
		if (a_mag_l(max, min)) // max is closer
		{
			// ft_printf("max is closer\n");
			if (max < 0)
			{
				while (max < -1)
				{
					rrs(b, 'b');
					// print_stack(*a, *b);
					max++;
				}
				pa(a, b);
				// print_stack(*a, *b);
			}
			else
			{
				while (max > 1)
				{
					rs(b, 'b');
					// print_stack(*a, *b);
					max--;
				}
				pa(a, b);
				// print_stack(*a, *b);
			}
			pushed_back++; // to rejoin back
		}
		else
		{
			// ft_printf("min is closer\n");
			if (min < 0)
			{
				while (min < -2)
				{
					rrs(b, 'b');
					// print_stack(*a, *b);
					min++;
				}
				pa(a, b);
				rs(a, 'a');
				// print_stack(*a, *b);
			}
			else
			{
				while (min > 2)
				{
					// ft_printf("min is %i steps away\n", min);
					rs(b, 'b');
					// print_stack(*a, *b);
					min--;
				}
				pa(a, b);
				rs(a, 'a');
				// print_stack(*a, *b);
			}
		}
	}
	while (pushed_back > 0)
	{
		// rrs(a, 'a');
		rs(a, 'a');
		pushed_back--;
		// print_stack(*a, *b);
	}
}

void	sort(t_list **a, t_list **b)
{
	int segment_size = 80;
	int asize = ft_lstsize(*a);
	int i = 0;
	while (i < asize)
	{
		int to = i + segment_size;
		if (to > asize)
			to = asize;
		// ft_printf("sorting %i - %i\n", i, to);
		sort_portion(a, b, i, to);
		i += segment_size;
	}
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	a = parse_input(argc, argv);
	if (!a)
		return (1);
	b = 0;
	sort_complex(&a, &b);
	// sort(&a, &b);

	print_stack(a, b);
	ft_lstclear(&a, lst_item_free);
	ft_lstclear(&b, lst_item_free);
}
