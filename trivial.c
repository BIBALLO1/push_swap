/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trivial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:09:18 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/29 00:47:10 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

static int	lst_at(t_list *a, int idx)
{
	return (((t_item *)(ft_lstidx(a, idx)->content))->index);
}

static void sort_two(t_list **a, char a_n)
{
	if (ft_lstsize(*a) >= 2 && lst_at(*a, 0) > lst_at(*a, 1))
		ss(a, a_n);
}

static void sort_three(t_list **a, char a_n)
{
	if (lst_at(*a, 0) < lst_at(*a, 1) && lst_at(*a, 1) < lst_at(*a, 2))
		return ;
	if (lst_at(*a, 0) > lst_at(*a, 1))
	{
		if (lst_at(*a, 0) > lst_at(*a, 2))
			rs(a, a_n);
		sort_two(a, a_n);
	}
	else 
	{
		rrs(a, a_n);
		sort_two(a, a_n);
	}
}

void	sort_trivial(t_list **a)
{
	if (ft_lstsize(*a) < 3)
	{
		sort_two(a, 'a');
		return ;
	}
	sort_three(a, 'a');
}
