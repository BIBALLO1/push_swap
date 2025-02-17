/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:24:28 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/17 13:16:26 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	lst_item_free(void *content)
{
	if (content)
		free(content);
}

int	lst_fill_indices(t_list *lst)
{
	t_item	*item;
	t_list	*next_min;
	int		threshold;
	int		i;

	if (!lst)
		return (-1);
	threshold = INT_MIN;
	next_min = lst_min_value(lst, threshold);
	i = 0;
	while (next_min != 0 && ((t_item *)(next_min->content))->index >= 0)
	{
		item = (t_item *)(next_min->content);
		item->index = i++;
		threshold = item->value;
		next_min = lst_min_value(lst, threshold);
	}
	return (!next_min);
}

int	add_arg(t_list **lst, const char *arg, const char **endptr)
{
	t_item	*item;
	t_list	*new;

	item = ft_calloc(1, sizeof(t_item));
	if (!item)
		return (0);
	new = ft_lstnew(item);
	if (!new)
	{
		free(item);
		return (0);
	}
	if (!ft_isint(arg))
		return (0);
	item->value = ft_strtol(arg, endptr);
	ft_lstadd_back(lst, new);
	return (1);
}

int	add_args(t_list **lst, const char *arg)
{
	const char	*nptr;

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
