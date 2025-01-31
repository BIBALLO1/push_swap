/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:18:03 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/31 13:43:43 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ss(t_list **lst, char stack)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;

	if (!lst || !(*lst) || !(*lst)->next)
		return ;
	first = *lst;
	second = first->next;
	third = second->next;
	first->next = third;
	second->next = first;
	*lst = second;
	ft_printf("s%c\n", stack);
}
