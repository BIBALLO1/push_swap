/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/28 12:07:15 by dmoraled         ###   ########.fr       */
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

void	sort(t_list **a, t_list **b)
{
	print_stack(*a, *b);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	a = parse_input(argc, argv);
	if (!a)
		return (1);
	b = 0;
	sort(&a, &b);
	// print_stack(a, b);
	ft_lstclear(&a, lst_item_free);
	ft_lstclear(&b, lst_item_free);
}
