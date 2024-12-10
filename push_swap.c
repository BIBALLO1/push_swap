/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/10 09:14:06 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	int		b_size;

	a = parse_input(argc, argv);
	if (!a)
		return (1);
	print_stack(a, b);
	while (ft_lstsize(a) > 0)
	{
		b_size = ft_lstsize(b);
		while (((t_item *)a->content)->index != b_size)
		{
			rs(&a);
			ft_printf("ra\n");
			print_stack(a, b);
		}
		pb(&a, &b);
		ft_printf("pb\n");
		print_stack(a, b);
	}
	while (ft_lstsize(b) > 0)
	{
		pa(&a, &b);
		ft_printf("pa\n");
		print_stack(a, b);
	}
	ft_lstclear(&a, lst_item_free);
	ft_lstclear(&b, lst_item_free);
}
