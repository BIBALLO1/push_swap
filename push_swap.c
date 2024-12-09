/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/04 17:14:11 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

void	lst_pb(t_list **a, t_list **b)
{
	t_list	*first;

	if (!a || !b || !(*a))
		return ;
	first = *a;
	*a = (*a)->next;
	ft_lstadd_front(b, first);
}

void	lst_pa(t_list **a, t_list **b)
{
	t_list	*first;

	if (!a || !b || !(*b))
		return ;
	first = *b;
	*b = (*b)->next;
	ft_lstadd_front(a, first);
}

void	lst_rot(t_list **lst)
{
	t_list	*last;
	t_list	*first;

	if (!lst || !(*lst) || !(*lst)->next)
		return ;
	last = ft_lstlast(*lst);
	first = *lst;
	*lst = (*lst)->next;
	first->next = 0;
	last->next = first;
}

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
	while (ft_lstsize(a) > 0)
	{
		b_size = ft_lstsize(b);
		while (((t_item *)a->content)->index != b_size)
		{
			lst_rot(&a);
			ft_printf("ra\n");
		}
		lst_pb(&a, &b);
		ft_printf("pb\n");
	}
	while (ft_lstsize(b) > 0)
	{
		lst_pa(&a, &b);
		ft_printf("pa\n");
	}
	ft_lstclear(&a, lst_item_free);
	ft_lstclear(&b, lst_item_free);
}
