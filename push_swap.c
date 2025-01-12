/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/12 14:14:21 by dmoraled         ###   ########.fr       */
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

void	sort_iter(t_list **a, t_list **b, int dig)
{
	int	v;
	int i;

	i = ft_lstsize(*a);
	while (a && *a && i > 0) {
		v = (((t_item *)(*a)->content)->index);
		if (!(v & (1 << dig))) {
			pb(a, b);
		} else {
			rs(a, 'a');
		}
		--i;
	}
	// print_stack(*a, *b);
	while (b && *b) {
		pa(a, b);
	}
}

int	num_bin_digits(int n)
{
	int c;

	c = 0;
	while (n > 0)
	{
		n /= 2;
		++c;
	}
	return c;
}

int	lst_max_binary_digits(t_list *lst)
{
	int	max;
	int	i;
	int	n;

	max = 0;
	while (lst)
	{
		i = ((t_item *)lst->content)->index;
		n = num_bin_digits(i);
		if (max < n)
			max = n;
		lst = lst->next;
	}
	return (max);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	int	iter;

	a = parse_input(argc, argv);
	if (!a)
		return (1);
	b = 0;
	iter = lst_max_binary_digits(a);
	int dig = 0;
	while (iter > 0)
	{
		// print_stack(a, b);
		sort_iter(&a, &b, dig);
		++dig;
		--iter;
	}
	// print_stack(a, b);
	ft_lstclear(&a, lst_item_free);
	ft_lstclear(&b, lst_item_free);
}
