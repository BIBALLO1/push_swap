/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:47:01 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/17 09:51:06 by dmoraled         ###   ########.fr       */
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
	ft_printf("rr%c\n", stack);
}
