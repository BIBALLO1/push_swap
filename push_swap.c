/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/17 10:39:10 by dmoraled         ###   ########.fr       */
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

int	lst_check_radix_val(t_list *lst, int dig, int val)
{
	int	ret;
	int	item_dig;
	
	ret = 1;
	while (lst) {
		item_dig = (((t_item *)lst->content)->index & (1 << dig)) != 0;
		if (item_dig ^ val)
		{
			ret = 0;
			break ;
		}
		lst = lst->next;
	}
	return ret;
}

void	sort_iter(t_list **a, t_list **b, int dig)
{
	while (a && *a) {
		if (lst_check_radix_val(*a, dig, 1))
			break ;
		if (!(((t_item *)(*a)->content)->index & (1 << dig))) {
			pb(a, b);
		} else {
			rs(a, 'a');
		}
	}
	int b_rots = 0;
	while (b && *b) {
		if (lst_check_radix_val(*b, dig, 0))
			break ;
		if ((((t_item *)(*b)->content)->index & (1 << dig))) {
			pa(a, b);
		} else {
			rs(b, 'b');
			b_rots++;
		}
	}
	while (b_rots > 0) {
		rrs(b, 'b');
		--b_rots;
	}
}

int	lst_max_binary_digits(t_list *lst)
{
	int	max = 0;

	while (lst)
	{

		lst = lst->next;
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
	int dig = 0;
	print_stack(a, b);
	sort_iter(&a, &b, dig);
	print_stack(a, b);
	++dig;
	sort_iter(&a, &b, dig);
	print_stack(a, b);
	while (b) {
		pa(&a, &b);
	}
	print_stack(a, b);
	ft_lstclear(&a, lst_item_free);
	ft_lstclear(&b, lst_item_free);
}
