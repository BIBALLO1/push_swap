/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:24:28 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/10 10:33:42 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	lst_item_free(void *content)
{
	if (content)
		free(content);
}

int	lst_item_less(void *a_content, void *b_content)
{
	t_item	*a;
	t_item	*b;

	a = ((t_item *)a_content);
	b = ((t_item *)b_content);
	return (a->index < b->index);
}

int	lst_min(t_list *lst, int threshold)
{
	int		min;
	int		min_idx;
	t_item	*item;
	int		curr_idx;

	min = INT_MAX;
	min_idx = -1;
	curr_idx = 0;
	while (lst)
	{
		item = (t_item *)lst->content;
		if (item->value < min && item->value > threshold)
		{
			min = item->value;
			min_idx = curr_idx;
		}
		lst = lst->next;
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

t_list	*parse_input(int argc, char **argv)
{
	t_list	*lst;
	t_item	*item;
	t_list	*new;

	lst = 0;
	item = 0;
	if (argc <= 1)
		return (0);
	while (argc > 1)
	{
		item = ft_calloc(1, sizeof(t_item));
		new = ft_lstnew(item);
		if (!item || !new)
		{
			ft_lstclear(&lst, lst_item_free);
			return (0);
		}
		item->value = ft_atoi(argv[argc - 1]);
		ft_lstadd_front(&lst, new);
		--argc;
	}
	lst_fill_indices(lst);
	return (lst);
}
