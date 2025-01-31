/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:47:01 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/31 13:45:59 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rs(t_list **lst, char stack)
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
	if (stack != 0)
		ft_printf("r%c\n", stack);
}

void	rrs(t_list **lst, char stack)
{
	t_list	*l;
	t_list	*first;

	if (!lst || !(*lst) || !(*lst)->next)
		return ;
	if (!((*lst)->next->next))
		return (rs(lst, stack));
	l = *lst;
	while (l->next->next)
	{
		l = l->next;
	}
	first = *lst;
	*lst = l->next;
	l->next = 0;
	(*lst)->next = first;
	if (stack != 0)
		ft_printf("rr%c\n", stack);
}

void	rr(t_list **a, t_list **b)
{
	rs(a, 0);
	rs(b, 0);
	ft_printf("rr\n");
}

void	rrr(t_list **a, t_list **b)
{
	rrs(a, 0);
	rrs(b, 0);
	ft_printf("rrr\n");
}
