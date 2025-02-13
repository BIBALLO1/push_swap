/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/13 12:33:55 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	a = parse_input(argc, argv);
	if (!a)
		return (1);
	if (is_sorted(a))
		return (0);
	b = 0;
	if (ft_lstsize(a) <= 5)
		sort_small(&a, &b);
	else
		sort_complex(&a, &b);
	ft_lstclear(&a, lst_item_free);
	ft_lstclear(&b, lst_item_free);
	return (0);
}
