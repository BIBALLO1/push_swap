/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:10:54 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/10 09:13:33 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pb(t_list **a, t_list **b)
{
	t_list	*first;

	if (!a || !b || !(*a))
		return ;
	first = *a;
	*a = (*a)->next;
	ft_lstadd_front(b, first);
}

void	pa(t_list **a, t_list **b)
{
	t_list	*first;

	if (!a || !b || !(*b))
		return ;
	first = *b;
	*b = (*b)->next;
	ft_lstadd_front(a, first);
}

void	rs(t_list **lst)
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
