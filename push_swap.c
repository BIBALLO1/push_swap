/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/04 11:56:44 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

int	lst_less(t_list *a, t_list *b)
{
	return (*(int *)(a->content) < *(int *)(b->content));
}

int	lst_min(t_list *lst, int threshold)
{
	t_list	*l;
	int		min;
	int		min_idx;
	t_item	*item;
	int		curr_idx;

	min = INT_MAX;
	min_idx = -1;
	curr_idx = 0;
	l = lst;
	while (l)
	{
		item = (t_item *)l->content;
		if (item->value < min && item->value > threshold)
		{
			min = item->value;
			min_idx = curr_idx;
		}
		l = l->next;
		++curr_idx;
	}
	return (min_idx);
}

void	lst_fill_indices(t_list *lst)
{
	t_item	*item;
	int		next_min_idx;
	int		threshold;
	int		i;

	threshold = INT_MIN;
	next_min_idx = lst_min(lst, threshold);
	i = 0;
	while (next_min_idx >= 0)
	{
		item = (t_item *)(ft_lstidx(lst, next_min_idx)->content);
		item->index = i++;
		threshold = item->value;
		next_min_idx = lst_min(lst, threshold);
	}
}

void	item_print(void *content)
{
	t_item	*item;

	item = (t_item *)content;
	ft_printf("[%i]:%i ", item->index, item->value);
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_item	*item;

	lst = 0;
	item = 0;
	if (argc <= 1)
	{
		ft_printf("no args : (\n");
		return (1);
	}
	while (argc > 1)
	{
		item = ft_calloc(1, sizeof(t_item));
		if (!item)
			return (1);
		item->value = ft_atoi(argv[argc - 1]);
		ft_lstadd_front(&lst, ft_lstnew(item));
		--argc;
	}
	lst_fill_indices(lst);
	ft_lstiter(lst, item_print);
	ft_lstclear(&lst, free);
}
