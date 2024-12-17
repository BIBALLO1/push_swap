/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:10:54 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/17 09:51:01 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	pb(t_list **a, t_list **b)
{
	t_list	*first;

	if (!a || !b || !(*a))
		return ;
	first = *a;
	*a = (*a)->next;
	ft_lstadd_front(b, first);
	ft_printf("pb\n");
}

void	pa(t_list **a, t_list **b)
{
	t_list	*first;

	if (!a || !b || !(*b))
		return ;
	first = *b;
	*b = (*b)->next;
	ft_lstadd_front(a, first);
	ft_printf("pa\n");
}
