/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/10 10:34:10 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

void	print_stack(t_list *a, t_list *b)
{
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

void	sort_iteration(t_list **a, t_list **b)
{
	int direction = 0;
	int last_direction = 0;

	while (ft_lstsize(*a) > 0)
	{
		if (direction == 0)
		{
			int f = ((t_item *)(*a)->content)->index;
			int l = ((t_item *)ft_lstlast(*a)->content)->index;
			if (((f > l && *b && ((t_item *)(*b)->content)->index < f)
				|| (f < l && *b && ((t_item *)(*b)->content)->index < l))
				&& last_direction == direction)
			{
				direction = 1;
				ft_printf("changing to smalls\n");
			}
			if (direction == 0)
			{
				ft_printf("(dir: bigs) first: %i, last: %i\n", f, l);
				if (f > l)
				{
					pb(a, b);
					ft_printf("pb\n");
					print_stack(*a, *b);
				}
				else
				{
					rrs(a);
					pb(a, b);
					ft_printf("rra\npb\n");
					print_stack(*a, *b);
				}
				last_direction = 0;
			}
		}
		else
		{
			int f = ((t_item *)(*a)->content)->index;
			int l = ((t_item *)ft_lstlast(*a)->content)->index;
			if (((f > l && *b && ((t_item *)(*b)->content)->index > l)
				|| (f < l && *b && ((t_item *)(*b)->content)->index > f))
				&& last_direction == direction)
			{
				direction = 0;
				ft_printf("changing to bigs\n");
			}
			if (direction > 0)
			{
				ft_printf("(dir: smalls) first: %i, last: %i\n", f, l);
				if (f < l)
				{
					pb(a, b);
					ft_printf("pb\n");
					print_stack(*a, *b);
				}
				else
				{
					rrs(a);
					pb(a, b);
					ft_printf("rra\npb\n");
					print_stack(*a, *b);
				}
				last_direction = 1;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	a = parse_input(argc, argv);
	if (!a)
		return (1);
	while (!ft_lstsorted(a, lst_item_less))
	{
		sort_iteration(&a, &b);
		ft_printf("--------------------------------------\n");
		sort_iteration(&b, &a);
		print_stack(a, b);
	}
	ft_lstclear(&a, lst_item_free);
	ft_lstclear(&b, lst_item_free);
}
