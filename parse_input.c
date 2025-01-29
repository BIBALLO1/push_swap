/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:24:28 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/29 11:45:07 by dmoraled         ###   ########.fr       */
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
	long	min;
	int		min_idx;
	t_item	*item;
	int		curr_idx;

	min = (long)INT_MAX + 1;
	min_idx = -1;
	curr_idx = 0;
	while (lst)
	{
		item = (t_item *)(lst->content);
		if (item->value == min)
			return (-2);
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

int	lst_fill_indices(t_list *lst)
{
	t_item	*item;
	int		next_min_idx;
	int		threshold;
	int		i;

	if (!lst)
		return (0);
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
	return (next_min_idx != -2);
}

int	add_arg(t_list **lst, const char *arg, const char **endptr)
{
	t_item	*item;
	t_list	*new;
	long	value;

	item = ft_calloc(1, sizeof(t_item));
	new = ft_lstnew(item);
	if (!item || !new)
		return (0);
	ft_strtol(arg, endptr);
	value = ft_atol(arg);
	if (!ft_isint(value))
		return (0);
	item->value = value;
	ft_lstadd_back(lst, new);
	return (1);
}

int	add_args(t_list **lst, const char *arg)
{
	const char *nptr;

	if (!ft_isnum(arg))
		return (0);
	nptr = arg;
	while (ft_isnum(nptr))
	{
		if (!add_arg(lst, nptr, &nptr))
			return (0);
	}
	return (1);
}

t_list	*parse_input(int argc, char **argv)
{
	t_list	*lst;
	int		arg_it;

	lst = 0;
	arg_it = 1;
	while (arg_it < argc)
	{
		if (!add_args(&lst, argv[arg_it]))
		{
			ft_lstclear(&lst, lst_item_free);
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
		++arg_it;
	}
	if (!lst_fill_indices(lst))
	{
		ft_lstclear(&lst, lst_item_free);
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	return (lst);
}
